// File JS_Basics.hh
#ifndef JS_BASICS_HH
#define JS_BASICS_HH

#include "JS_Data.hh"

class JS_State
{  
  friend ostream& operator<<(ostream& os, const JS_State& st);
  friend bool operator==(const JS_State& st1, const JS_State& st2);
public:
  JS_State(const JS_Input &in);
  JS_State& operator=(const JS_State& s);
protected:
  const JS_Input & in; 
  vector<vector<unsigned>> disjuntive_graphs;//given i job, starting_times[i] tells the starting times of its tasks.


};

class JS_Move
{
  friend bool operator==(const JS_Move& m1, const JS_Move& m2);
  friend bool operator!=(const JS_Move& m1, const JS_Move& m2);
  friend bool operator<(const JS_Move& m1, const JS_Move& m2);
  friend ostream& operator<<(ostream& os, const JS_Move& c);
  friend istream& operator>>(istream& is, JS_Move& c);
 public:
  JS_Move();
};
#endif

