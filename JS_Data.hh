// File JS_Data.hh
#ifndef JS_DATA_HH
#define JS_DATA_HH

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <tuple>

using namespace std;

class JS_Output;



class JS_Input 
{

  friend class JS_State;

  friend class JS_Output;
  
  friend ostream& operator<<(ostream& os, const JS_Input& bs);
public:
  JS_Input(string file_name);
  // Insert your getters

  
protected:
  // Insert your data members
  unsigned n_Jobs;
  unsigned n_Machines;
  vector<vector<tuple<unsigned,unsigned,unsigned>>> tasks;
  vector<unsigned> release_dates;
  vector<int> due_dates;

  vector<unsigned> n_task_per_Job;


  //tasks[i].size();//number of task of job i;




};

class JS_Output 
{
  friend ostream& operator<<(ostream& os, const JS_Output& out);
  friend istream& operator>>(istream& is, JS_Output& out);
public:
  JS_Output(const JS_Input& i);
  JS_Output& operator=(const JS_Output& out);
  // Insert your getters
protected:
  const JS_Input& in;
  // Insert your data members
  vector<vector<unsigned>> starting_times;//given i job, starting_times[i] tells the starting times of its tasks.

  };
#endif
