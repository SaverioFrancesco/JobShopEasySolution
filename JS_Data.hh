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
  unsigned NumMachines() const { return n_Machines; }
  unsigned NumJobs() const { return n_Jobs; }
  tuple<unsigned,unsigned,unsigned> Task(unsigned j, unsigned t) const { return tasks[j][t]; }
  unsigned ReleaseDate(unsigned j) const { return release_dates[j]; }
  unsigned DueDate(unsigned j) const { return due_dates[j]; }
  unsigned NumTasksOfMachine(unsigned m) const { return n_task_per_machine[m]; }
  unsigned NumTaskOfJob(unsigned j) const { return n_task_per_Job[j]; }
  vector<tuple<unsigned,unsigned,unsigned>> TasksOfMachine(unsigned m) const { return tasks_of_machine[m]; }
  
protected:
  // Insert your data members
  unsigned n_Jobs;
  unsigned n_Machines;
  vector<vector<tuple<unsigned,unsigned,unsigned>>> tasks;
  vector<unsigned> release_dates;
  vector<int> due_dates;

  vector<unsigned> n_task_per_Job;
  vector<unsigned> n_task_per_machine;
  vector<vector<tuple<unsigned,unsigned,unsigned>>> tasks_of_machine;
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
  void Reset() { starting_times.clear(); }
  void SetStartingTime(unsigned job, tuple<unsigned,unsigned,unsigned> task, unsigned duration, unsigned m);
protected:
  const JS_Input& in;
  // Insert your data members
  vector<vector<unsigned>> starting_times;//given i job, starting_times[i] tells the starting times of its tasks.

};
#endif
