// File JS_Data.cc
#include "JS_Data.hh"
#include <fstream>
#include <cassert>

template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";     
    return os;
}

template < class T , class K, class G >
std::ostream& operator << (std::ostream& os, const std::tuple<T,K,G>& v) 
{
    os << "<";
    os << get<0>(v) <<", "<< get<1>(v) << ", " << get<2>(v);
    os << ">";
    return os;
}


JS_Input::JS_Input(string file_name)
{
  // Insert the code that reads the input from the file 
  // and stored it into the data structures of the object 

  ifstream is(file_name.c_str());
  assert(!is.fail());
  
  is >> n_Jobs>> n_Machines;
  
  tasks.resize(0);
  release_dates.resize(n_Jobs);
  due_dates.resize(n_Jobs);
  n_task_per_Job.resize(n_Jobs);
  n_task_per_machine.resize(n_Machines);
  for (unsigned m = 0; m < n_Machines; m++)
    n_task_per_machine[m] = 0;
  
  for (unsigned s = 0; s < n_Jobs; s++)
  {
    std::vector<tuple<unsigned,unsigned,unsigned>> current_job;
    unsigned n_task;
    is >> n_task;
    n_task_per_Job[s]=n_task;

    tuple<unsigned,unsigned,unsigned> task_tuple(0,0,s);
    current_job.resize(n_task, task_tuple);//s è  l'indice del job a cui appartiene questo task.

    unsigned aux;
    for (unsigned i = 0; i < n_task; ++i)
    {
      is >> aux;
      get<0>(current_job[i])= aux; //duration
    }
    for (unsigned i = 0; i < n_task; ++i)
    {
      is >> aux;
      get<1>(current_job[i])=  aux; //machine
      n_task_per_machine[aux]++;
    }

    tasks.push_back(current_job);

    is >> aux;
    release_dates[s]=aux;
    int due;
    is >> due;
    due_dates[s]=due;

  }

}

ostream& operator<<(ostream& os, const JS_Input& pa)
{
  // Insert the code that write the input object (needed for debugging purposes)
  os << "=== Input data ===" << endl;
  os << "Num Jobs: " << pa.NumJobs() << ", Num Machines: " << pa.NumMachines() << endl;

  for (unsigned j = 0; j < pa.NumJobs(); j++){
    os << "Job " << j << ", Num of Tasks: " << pa.NumTaskOfJob(j) << ", Tasks: ";
    for (unsigned t = 0; t < pa.NumTaskOfJob(j); t++)
     os << pa.tasks[j][t] << " ";
    os << std::endl;
  }
  
  return os;
}

JS_Output::JS_Output(const JS_Input& my_in)
  : in(my_in)
{
  // Insert the code that initialize the data structures of the
  // output object based in the input object
  starting_times.resize(my_in.n_Jobs);

  for (unsigned i = 0; i < my_in.n_Jobs; ++i)
  {
    starting_times[i].resize(my_in.tasks[i].size()); 
  }

  //cerr << "JS_Output::JS_Output(const JS_Input&) not implemented yet" << endl;
}

JS_Output& JS_Output::operator=(const JS_Output& out)	
{
  // Insert the code that copies all data structures of the
  // output object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)

  this->starting_times = out.starting_times;

  //throw logic_error("JS_Output::operator= not implemented yet");	
  return *this;
}


ostream& operator<<(ostream& os, const JS_Output& out)
{ 
 // Insert the code that writes the output object
  //
  
  os<< out.starting_times;
  //throw logic_error("operator<<(ostream& os, const JS_Output& out) not implemented yet");		
  return os;
}

istream& operator>>(istream& is, JS_Output& out)
{
  // Insert the code that reads the output object
  throw logic_error("operator>>(istream& is, JS_Output& out) not implemented yet");	
  return is;
}
