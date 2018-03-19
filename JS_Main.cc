#include "JS_Helpers.hh"

#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>


using namespace EasyLocal::Debug;

int main(int argc, const char* argv[])
{
  ParameterBox main_parameters("main", "Main Program options");

  // The set of arguments added are the following:
  
  Parameter<string> instance("instance", "Input instance", main_parameters); 
  Parameter<int> seed("seed", "Random seed", main_parameters);
  Parameter<string> method("method", "Solution method (empty for tester)", main_parameters);   
  Parameter<string> init_state("init_state", "Initial state (to be read from file)", main_parameters);
  Parameter<unsigned> observer("observer", "Attach the observers", main_parameters);
  Parameter<string> output_file("output_file", "Write the output to a file (filename required)", main_parameters);
 
  // 3rd parameter: false = do not check unregistered parameters
  // 4th parameter: true = silent
  CommandLineParameters::Parse(argc, argv, false, true);  

  if (!instance.IsSet())
    {
      cout << "Error: --main::instance filename option must always be set" << endl;
      return 1;
    }
  JS_Input in(instance);

  cout << in;

  if (seed.IsSet())
    Random::Seed(seed);
  
  // cost components: second parameter is the cost, third is the type (true -> hard, false -> soft)
  JS_CostComponent1 cc1(in, 1, true);
  JS_CostComponent2 cc2(in, 1, true);
 
  JS_MoveDeltaCostComponent1 dcc1(in, cc1);
  JS_MoveDeltaCostComponent2 dcc2(in, cc2);

  // helpers
  JS_StateManager JS_sm(in);
  JS_MoveNeighborhoodExplorer JS_nhe(in, JS_sm);

  JS_OutputManager JS_om(in);
  
  // All cost components must be added to the state manager
  JS_sm.AddCostComponent(cc1);
  JS_sm.AddCostComponent(cc2);
  
  // All delta cost components must be added to the neighborhood explorer
  JS_nhe.AddDeltaCostComponent(dcc1);
  JS_nhe.AddDeltaCostComponent(dcc2);
  
  // runners
  HillClimbing<JS_Input, JS_State, JS_Move> JS_hc(in, JS_sm, JS_nhe, "JS_MoveHillClimbing");
  SteepestDescent<JS_Input, JS_State, JS_Move> JS_sd(in, JS_sm, JS_nhe, "JS_MoveSteepestDescent");
  SimulatedAnnealing<JS_Input, JS_State, JS_Move> JS_sa(in, JS_sm, JS_nhe, "JS_MoveSimulatedAnnealing");

  // tester
  Tester<JS_Input, JS_Output, JS_State> tester(in,JS_sm,JS_om);
  MoveTester<JS_Input, JS_Output, JS_State, JS_Move> swap_move_test(in,JS_sm,JS_om,JS_nhe, "JS_Move move", tester); 

  SimpleLocalSearch<JS_Input, JS_Output, JS_State> JS_solver(in, JS_sm, JS_om, "JS solver");
  if (!CommandLineParameters::Parse(argc, argv, true, false))
    return 1;

  if (!method.IsSet())
    { // If no search method is set -> enter in the tester
      if (init_state.IsSet())
	    tester.RunMainMenu(init_state);
      else
	    tester.RunMainMenu();
    }
  else
    {

      if (method == string("SA"))
        {
          JS_solver.SetRunner(JS_sa);
        }
      else if (method == string("HC"))
        {
          JS_solver.SetRunner(JS_hc);
        }
      else // if (method.GetValue() == string("SD"))
        {
          JS_solver.SetRunner(JS_sd);
        }
      auto result = JS_solver.Solve();
	  // result is a tuple: 0: solutio, 1: number of violations, 2: total cost, 3: computing time
      JS_Output out = result.output;
      if (output_file.IsSet())
        { // write the output on the file passed in the command line
          ofstream os(static_cast<string>(output_file).c_str());
          os << out << endl;
          os << "Cost: " << result.cost.total << endl;
					os << "Time: " << result.running_time << "s " << endl;
          os.close();
        }
      else
        { // write the solution in the standard output
          cout << out << endl;
          cout << "Cost: " << result.cost.total << endl;
					cout << "Time: " << result.running_time << "s " << endl;					
        }
   }
  return 0;
}
