// File JS_Basics.cc
#include "JS_Basics.hh"

JS_State::JS_State(const JS_Input &my_in) 
  : in(my_in)
{
  // Insert the code that initialized the data structure of the
  // state object based on the input object	
  disjuntive_graphs.resize(my_in.n_Jobs);
  for (unsigned i = 0; i < my_in.n_Jobs; ++i)
  {
    disjuntive_graphs[i].resize(my_in.n_task_per_Job[i]);
  }

}

JS_State& JS_State::operator=(const JS_State& st)
{
  // Insert the code that copies all data structures of the
  // state object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)

  this->disjuntive_graphs =  st.disjuntive_graphs;


  return *this;
}
  
bool operator==(const JS_State& st1, const JS_State& st2)
{
  // Insert the code that compares two states (this is used by the tester)

  return  st1.disjuntive_graphs == st2.disjuntive_graphs;

}


ostream& operator<<(ostream& os, const JS_State& st)
{
  // Insert the code that writes the state object (for debugging)
  
  os << st.disjuntive_graphs;

  return os;
}

JS_Move::JS_Move()
{
  // Insert the code that initialize the move
  cerr << "JS_Move::JS_Move() not implemented yet" << endl;
}

bool operator==(const JS_Move& mv1, const JS_Move& mv2)
{
  // Insert the code that checks if two moves are identical
  throw logic_error("operator==(const JS_Move& mv1, const JS_Move& mv2) not implemented yet");	
  return true;
}

bool operator!=(const JS_Move& mv1, const JS_Move& mv2)
{
  // Insert the code that checks if two moves are different
  throw logic_error("operator!=(const JS_Move& mv1, const JS_Move& mv2) not implemented yet");	
  return true;
}

bool operator<(const JS_Move& mv1, const JS_Move& mv2)
{
  // Insert the code that checks if one move precedes another one
  // (in any selected order)
  throw logic_error("operator<(const JS_Move& mv1, const JS_Move& mv2) not implemented yet");	
  return true;
}

istream& operator>>(istream& is, JS_Move& mv)
{
  // Insert the code that read a move
  throw logic_error("operator>>(istream& is, JS_Move& cìmv) not implemented yet");	
  return is;
}

ostream& operator<<(ostream& os, const JS_Move& mv)
{
  // Insert the code that writes a move
  throw logic_error("operator<<(ostream& os, const JS_Move& mv) not implemented yet");	
  return os;
}
