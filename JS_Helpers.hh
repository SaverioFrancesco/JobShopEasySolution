// File JS_Helpers.hh
#ifndef JS_HELPERS_HH
#define JS_HELPERS_HH

#include "JS_Basics.hh"
#include <easylocal/easylocal.hh>
#include <algorithm>


using namespace EasyLocal::Core;

/***************************************************************************
 * State Manager 
 ***************************************************************************/

class JS_CostComponent1 : public CostComponent<JS_Input,JS_State> 
{
public:
  JS_CostComponent1(const JS_Input & in, int w, bool hard) 
    : CostComponent<JS_Input,JS_State>(in,w,hard,"JS_CostComponent1") 
  {}
  int ComputeCost(const JS_State& st) const;
  void PrintViolations(const JS_State& st, ostream& os = cout) const;
};

class JS_CostComponent2: public CostComponent<JS_Input,JS_State> 
{
public:
  JS_CostComponent2(const JS_Input & in, int w, bool hard) 
    : CostComponent<JS_Input,JS_State>(in,w,hard,"JS_CostComponent2") 
  {}
  int ComputeCost(const JS_State& st) const;
  void PrintViolations(const JS_State& st, ostream& os = cout) const;
};

class JS_StateManager : public StateManager<JS_Input,JS_State> 
{
public:
  JS_StateManager(const JS_Input &);
  void RandomState(JS_State&);   
  bool CheckConsistency(const JS_State& st) const;
protected:
}; 

/***************************************************************************
 * SwapJS Neighborhood Explorer:
 ***************************************************************************/

class SwapJSDeltaCostComponent1
  : public DeltaCostComponent<JS_Input,JS_State,SwapJS>
{
public:
  SwapJSDeltaCostComponent1(const JS_Input & in, JS_CostComponent1& cc) 
    : DeltaCostComponent<JS_Input,JS_State,SwapJS>(in,cc,"SwapJSDeltaCostComponent1") 
  {}
  int ComputeDeltaCost(const JS_State& st, const SwapJS& mv) const;
};

class SwapJSDeltaCostComponent2
  : public DeltaCostComponent<JS_Input,JS_State,SwapJS>
{
public:
  SwapJSDeltaCostComponent2(const JS_Input & in, JS_CostComponent2& cc) 
    : DeltaCostComponent<JS_Input,JS_State,SwapJS>(in,cc,"SwapJSDeltaCostComponent2") 
  {}
  int ComputeDeltaCost(const JS_State& st, const SwapJS& mv) const;
};

class SwapJSNeighborhoodExplorer
  : public NeighborhoodExplorer<JS_Input,JS_State,SwapJS> 
{
public:
  SwapJSNeighborhoodExplorer(const JS_Input & pin, StateManager<JS_Input,JS_State>& psm)  
    : NeighborhoodExplorer<JS_Input,JS_State,SwapJS>(pin, psm, "SwapJSNeighborhoodExplorer") {} 
  void RandomMove(const JS_State&, SwapJS&) const throw(EmptyNeighborhood);          
  bool FeasibleMove(const JS_State&, const SwapJS&) const;  
  void MakeMove(JS_State&,const SwapJS&) const;             
  void FirstMove(const JS_State&,SwapJS&) const throw(EmptyNeighborhood);  
  bool NextMove(const JS_State&,SwapJS&) const;   
protected:
};

/***************************************************************************
 * Output Manager:
 ***************************************************************************/
class JS_OutputManager
  : public OutputManager<JS_Input,JS_Output,JS_State> 
{
public:
  JS_OutputManager(const JS_Input & pin)
    : OutputManager<JS_Input,JS_Output,JS_State>(pin,"JSOutputManager") {}
  void InputState(JS_State&, const JS_Output&) const;  
  void OutputState(const JS_State&, JS_Output&) const; 
}; 
#endif
