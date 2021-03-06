#include "Market.h"

EGT::Market& EGT::Market::Instance(const std::string& signal_)
{
  static Market theMarket(signal_);
  return theMarket;
}


EGT::Market::Market(const std::string& signalStart_) : signalStart(signalStart_), signal(signalStart), currentResult(true), historyResult(0,0)
{

}

void EGT::Market::UpdateSignal(unsigned getResult)
{
  myUtils::check((getResult<2), "ERROR! EGT::Market::UpdateSignal()");
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
  myUtils::check((memsize<MEMMAX), "EGT::Market::GetSignal()");
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
