// File JS_Basics.hh
#ifndef JS_BASICS_HH
#define JS_BASICS_HH

#include "JS_Data.hh"

#include "graph.hh"
#include <cstdlib>
#include <tuple>

class JS_State
{  
  friend ostream& operator<<(ostream& os, const JS_State& st);
  friend bool operator==(const JS_State& st1, const JS_State& st2);
public:
  JS_State(const JS_Input &in);
  JS_State& operator=(const JS_State& s);
  void Reset();
  void SetTasksOfMachine(unsigned m, vector<tuple<unsigned,unsigned,unsigned>> v);
  vector<tuple<unsigned,unsigned,unsigned>> GetTasksOfMachine(unsigned m) const;
  tuple<unsigned,unsigned,unsigned> SelectedTask (unsigned m, unsigned p) const;
protected:
  const JS_Input & in; 
  vector<vector<tuple<unsigned, unsigned, unsigned>>> disjuntive_graphs;
  // tuples are made by: duration of the task, machine required, job to which the task belongs
  //Graph::graph<int,int> tasks_graph(graph_vect);

};

class SwapJS
{
  friend bool operator==(const SwapJS& m1, const SwapJS& m2);
  friend bool operator!=(const SwapJS& m1, const SwapJS& m2);
  friend bool operator<(const SwapJS& m1, const SwapJS& m2);
  friend ostream& operator<<(ostream& os, const SwapJS& c);
  friend istream& operator>>(istream& is, SwapJS& c);
 public:
  SwapJS(unsigned m_id = 0, unsigned pos1 = 0, unsigned po2 = 0);
  unsigned m, p1, p2;
};
#endif

