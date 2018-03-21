// File JS_Helpers.cc
#include "JS_Helpers.hh"

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
	throw logic_error("JS_OutputManager::OutputState not implemented yet");	
}


/*****************************************************************************
 * JS_Move Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void JS_MoveNeighborhoodExplorer::RandomMove(const JS_State& st, JS_Move& mv) const  throw(EmptyNeighborhood)
{
  // insert the code that writes a random move on mv in state st
	throw logic_error("JS_MoveNeighborhoodExplorer::RandomMove not implemented yet");	
} 

// check move feasibility
bool JS_MoveNeighborhoodExplorer::FeasibleMove(const JS_State& st, const JS_Move& mv) const
{
  // Insert the code that check is move mv is legal in state st 
  // (return true if legal, false otherwise)
	throw logic_error("JS_MoveNeighborhoodExplorer::FeasibleMove not implemented yet");	
  return true;
} 

// update the state according to the move 
void JS_MoveNeighborhoodExplorer::MakeMove(JS_State& st, const JS_Move& mv) const
{
  // Insert the code that modify the state st based on the application of move mv
	throw logic_error("JS_MoveNeighborhoodExplorer::MakeMove not implemented yet");	
}  

void JS_MoveNeighborhoodExplorer::FirstMove(const JS_State& st, JS_Move& mv) const  throw(EmptyNeighborhood)
{
  // Insert the code the generate the first move in the neighborhood and store it in mv
	throw logic_error("JS_MoveNeighborhoodExplorer::FirstMove not implemented yet");	
}

bool JS_MoveNeighborhoodExplorer::NextMove(const JS_State& st, JS_Move& mv) const
{
  // Insert the code that generate the move that follows mv in the neighborhood, and writes
  // it back in mv. Return false if mv is already the last move. 
	throw logic_error("JS_MoveNeighborhoodExplorer::NextMove not implemented yet");	
  return true;
}

int JS_MoveDeltaCostComponent1::ComputeDeltaCost(const JS_State& st, const JS_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("JS_MoveDeltaCostComponent1::ComputeDeltaCost not implemented yet");	
  return cost;
}
          
int JS_MoveDeltaCostComponent2::ComputeDeltaCost(const JS_State& st, const JS_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("JS_MoveDeltaCostComponent2::ComputeDeltaCost not implemented yet");	
  return cost;
}

