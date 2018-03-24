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

void JS_State::Reset()
{
  for (unsigned m = 0; m < in.NumMachines(); ++m)
    for (unsigned j = 0; j < in.NumTasksOfMachine(m); ++j)
      disjuntive_graphs[m][j] = make_tuple(0, 0, 0);
}

void JS_State::SetTasksOfMachine(unsigned m, vector<tuple<unsigned,unsigned,unsigned>> v)
{
  disjuntive_graphs[m] = v; 
}

vector<tuple<unsigned,unsigned,unsigned>> JS_State::GetTasksOfMachine(unsigned m) const
{
  return disjuntive_graphs[m];
}

tuple<unsigned,unsigned,unsigned> JS_State::SelectedTask(unsigned m, unsigned p) const
{
  return disjuntive_graphs[m][p];
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

SwapJS::SwapJS(unsigned m_id, unsigned pos1, unsigned pos2)
{
  // Insert the code that initialize the move
  m = m_id;
  p1 = pos1;
  p2 = pos2;
}

bool operator==(const SwapJS& mv1, const SwapJS& mv2)
{
  // Insert the code that checks if two moves are identical
  return mv1.m == mv2.m && mv1.p1 == mv2.p1 && mv1.p2 == mv2.p2;
}

bool operator!=(const SwapJS& mv1, const SwapJS& mv2)
{
  // Insert the code that checks if two moves are different
  return ! (mv1 == mv2);
}

bool operator<(const SwapJS& mv1, const SwapJS& mv2)
{
  // Insert the code that checks if one move precedes another one
  // (in any selected order)
  return (mv1.m < mv2.m 
    || (mv1.m == mv2.m && mv1.p1 < mv2.p1)
    || (mv1.m == mv2.m && mv1.p1 == mv2.p1 && mv1.p2 < mv2.p2));
}

istream& operator>>(istream& is, SwapJS& mv)
{
  // Insert the code that read a move
  char tmp;
  is >> tmp >> mv.m >> tmp >> mv.p1 >> tmp >> mv.p2 >> tmp;
  return is;
}

ostream& operator<<(ostream& os, const SwapJS& mv)
{
  // Insert the code that writes a move
  os << "<" << mv.m << "," << mv.p1 << "," << mv.p2 << ">";
  return os;
}
