#include "Market.h"

EGT::Market::Market(const std::string& signalStart_) : signalStart(signalStart_), signal(signalStart), currentResult(true), historyResult(0,0)
{

}

void EGT::Market::UpdateSignal(unsigned getResult)
{
  myUtils::error_testing((getResult<2), "ERROR! EGT::Market::UpdateSignal()");
  currentResult = getResult;
  signal <<= 1;

  if(getResult == 1) {
    signal.set(0);
    historyResult.first++;
  }
  else {
    signal.reset(0);
    historyResult.second++;
  }

}

void EGT::Market::ResetSignal()
{
  signal = *(new std::bitset<MEMMAX>(signalStart));
}

unsigned long EGT::Market::GetSignal(unsigned memsize) const
{
  myUtils::error_testing((memsize<MEMMAX), "EGT::Market::GetSignal()");
  unsigned long tmpSignal=0;
  for(unsigned ibit=memsize; ibit>0; ibit--) {
    tmpSignal = 2*tmpSignal + signal[ibit-1];
  }
  return tmpSignal;
}

unsigned EGT::Market::GetMaxMemSize() const
{
  return static_cast<unsigned>(MEMMAX);
}

void EGT::Market::ShowSignal() const
{
  std::cout<<signal<<std::endl;
}
