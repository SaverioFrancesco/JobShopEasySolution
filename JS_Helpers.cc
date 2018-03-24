// File JS_Helpers.cc
#include "JS_Helpers.hh"


int JS_CostScheduling::ComputeCost(const JS_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
  std::vector<std::pair<unsigned, unsigned> > graph_vect;
  
  //Let's add 2 fake tasks (0 and num_Task+1?) 
  unsigned num_Task= tot(st.in.n_task_per_Job)

  for (unsigned task_id = 0; task_id < num_Task; ++task_id)
  {
      graph_vect.push_back(std::pair<unsigned, unsigned>(task1, task2));
  }


  


  //Build the Adj List.
  Graph::graph<unsigned,unsigned> my_graph(graph_vect);

  //Compute dijkstra algo. over the graph to determinate erliyest starting times.

  //Compute makespan and violations in linear time.

  //throw logic_error("JS_CostComponent1::ComputeCost not implemented yet");  
  return cost;
}
          
void JS_CostScheduling::PrintViolations(const JS_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
  throw logic_error("JS_CostComponent1::PrintViolations not implemented yet");  
}

int JS_CostComponent1::ComputeCost(const JS_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
	throw logic_error("JS_CostComponent1::ComputeCost not implemented yet");	
  return cost;
}
          
void JS_CostComponent1::PrintViolations(const JS_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("JS_CostComponent1::PrintViolations not implemented yet");	
}

int JS_CostComponent2::ComputeCost(const JS_State& st) const
{ 
  unsigned cost = 0;
  // Insert the code that computes the cost for component 2
  // of state st
	throw logic_error("JS_CostComponent2::ComputeCost not implemented yet");	
  return cost;
}
 
void JS_CostComponent2::PrintViolations(const JS_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("JS_CostComponent2::PrintViolations not implemented yet");	
}

// constructor
JS_StateManager::JS_StateManager(const JS_Input & pin) 
  : StateManager<JS_Input,JS_State>(pin, "JSStateManager")  {} 

// initial state builder (random rooms)
void JS_StateManager::RandomState(JS_State& st) 
{
  // Insert the code that creates a random state in object st
	st.Reset();
  for (unsigned m = 0; m < in.NumMachines(); ++m)
  {
    vector<tuple<unsigned,unsigned,unsigned>> tmp;
    tmp = in.TasksOfMachine(m);
    random_shuffle(tmp.begin(), tmp.end());
    st.SetTasksOfMachine(m, tmp);
  }
} 

bool JS_StateManager::CheckConsistency(const JS_State& st) const
{
  // Insert the code that checks if state in object st is consistent
  // (for debugging purposes)
	throw logic_error("JS_StateManager::CheckConsistency not implemented yet");	
  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void JS_OutputManager::InputState(JS_State& st, const JS_Output& JS) const 
{
  // Insert the code that "translates" an output object to a state object
	throw logic_error("JS_OutputManager::InputState not implemented yet");	
}

void JS_OutputManager::OutputState(const JS_State& st, JS_Output& JS) const 
{
  // Insert the code that "translates" a state object to an output object
  JS.Reset();
  for (unsigned m = 0; m < in.NumMachines(); m++)
    for (unsigned p = 0; p < in.NumTasksOfMachine(m); p++)
    {
      // tuple<unsigned,unsigned,unsigned> task = st.SelectedTask(m, p);
      // here we need to have the starting times of the tasks in such a way to fill the output object
    }
    
	throw logic_error("JS_OutputManager::OutputState TODO");	
}


/*****************************************************************************
 * SwapJS Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void SwapJSNeighborhoodExplorer::RandomMove(const JS_State& st, SwapJS& mv) const  throw(EmptyNeighborhood)
{
  // insert the code that writes a random move on mv in state st
	throw logic_error("SwapJSNeighborhoodExplorer::RandomMove not implemented yet");	
} 

// check move feasibility
bool SwapJSNeighborhoodExplorer::FeasibleMove(const JS_State& st, const SwapJS& mv) const
{
  // Insert the code that check is move mv is legal in state st 
  // (return true if legal, false otherwise)

  return mv.p1 < mv.p2; // ordine lessicografico sulle mosse, la macchina sul quale viene eseguita la mossa non conta


	//throw logic_error("SwapJSNeighborhoodExplorer::FeasibleMove not implemented yet");	
  return true;
} 

// update the state according to the move 
void SwapJSNeighborhoodExplorer::MakeMove(JS_State& st, const SwapJS& mv) const
{
  // Insert the code that modify the state st based on the application of move mv
  vector<tuple<unsigned,unsigned,unsigned>> tmpv = st.GetTasksOfMachine(mv.m);
  tuple<unsigned,unsigned,unsigned> tmpt = tmpv[mv.p1];
  tmpv[mv.p1] = tmpv[mv.p2];
  tmpv[mv.p2] = tmpt;
  st.SetTasksOfMachine(mv.m, tmpv);
}  

void SwapJSNeighborhoodExplorer::FirstMove(const JS_State& st, SwapJS& mv) const  throw(EmptyNeighborhood)
{
  // Insert the code the generate the first move in the neighborhood and store it in mv
  mv.m = 0;
  mv.p1 = 0;
  mv.p2 = 1;
	//throw logic_error("SwapJSNeighborhoodExplorer::FirstMove CHECK");	
}

bool SwapJSNeighborhoodExplorer::NextMove(const JS_State& st, SwapJS& mv) const
{
  // Insert the code that generate the move that follows mv in the neighborhood, and writes
  // it back in mv. Return false if mv is already the last move. 
  if (mv.p2 < in.NumTasksOfMachine(mv.m) - 1)
  {
    mv.p2++;
    return true;
  }
  // then: mv.p2 == in.NumTasksOfMachine(mv.m) - 1
  if (mv.p1 < in.NumTasksOfMachine(mv.m) - 2)
  {
    mv.p1++;
    mv.p2 = mv.p1 + 1;
    return true;
  }
  // then: mv.p2 == in.NumTasksOfMachine(mv.m) - 1 && mv.p1 == in.NumTasksOfMachine(mv.m) - 2
  if (mv.m < in.NumMachines() - 1)
  {
    mv.m++;
    mv.p1 = 0;
    mv.p2 = mv.p1 + 1;
    return true;
  }
  // then: mv.p2 == in.NumTasksOfMachine(mv.m) - 1 && mv.p1 == in.NumTasksOfMachine(mv.m) - 2 && mv.m == in.NumMachines() - 1
  return false;
}

int SwapJSDeltaCostComponent1::ComputeDeltaCost(const JS_State& st, const SwapJS& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("SwapJSDeltaCostComponent1::ComputeDeltaCost not implemented yet");	
  return cost;
}
          
int SwapJSDeltaCostComponent2::ComputeDeltaCost(const JS_State& st, const SwapJS& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("SwapJSDeltaCostComponent2::ComputeDeltaCost not implemented yet");	
  return cost;
}

