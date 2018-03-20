// File JS_Basics.cc
#include "JS_Basics.hh"

JS_State::JS_State(const JS_Input &my_in) 
  : in(my_in)
{
  // Insert the code that initialized the data structure of the
  // state object based on the input object	
  disjuntive_graphs.resize(in.NumMachines());

  vector<unsigned> vec_cont;
  vec_cont.resize(in.NumMachines(), 0);
  for (unsigned m = 0; m < in.NumMachines(); m++)
    disjuntive_graphs[m].resize(in.NumTasksOfMachine(m), make_tuple(0, 0, 0));
  
  for (unsigned i = 0; i < in.NumJobs(); ++i)
    for (unsigned j = 0; j < in.NumTaskOfJob(i); ++j)
    {
      unsigned machine_id = get<1>(in.Task(i, j));
      disjuntive_graphs[machine_id][vec_cont[machine_id]++] = in.Task(i, j);
    }
}

JS_State& JS_State::operator=(const JS_State& st)
{
  // Insert the code that copies all data structures of the
  // state object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)
  this->disjuntive_graphs = st.disjuntive_graphs;
  return *this;
}
  
bool operator==(const JS_State& st1, const JS_State& st2)
{
  // Insert the code that compares two states (this is used by the tester)
  for (unsigned m=0; m<st1.in.NumMachines(); m++)
    for (unsigned j=0; j<st1.in.NumTasksOfMachine(m); j++)
      if ((get<0>(st1.disjuntive_graphs[m][j]) != get<0>(st2.disjuntive_graphs[m][j]))
        || (get<1>(st1.disjuntive_graphs[m][j]) != get<1>(st2.disjuntive_graphs[m][j]))
        || (get<2>(st1.disjuntive_graphs[m][j]) != get<2>(st2.disjuntive_graphs[m][j])))
        return false;
  return true;
}

ostream& operator<<(ostream& os, const JS_State& st)
{
  os << "=== State ===" << std::endl;
  // Insert the code that writes the state object (for debugging)
  for (unsigned m=0; m<st.in.NumMachines(); m++)
  {
    os << "Num Tasks on Machine " << m << ": " << st.in.NumTasksOfMachine(m) << std::endl;
    for (unsigned j=0; j<st.in.NumTasksOfMachine(m); j++)
      os << get<0>(st.disjuntive_graphs[m][j]) << " " 
         << get<1>(st.disjuntive_graphs[m][j]) << " " 
         << get<2>(st.disjuntive_graphs[m][j]) << " "
         << std::endl;
  }
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
