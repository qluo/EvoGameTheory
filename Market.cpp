#include "Market.h"
//#include "MyUtils.h"

EGT::Market::Market(const std::string& signalStart_) : signalStart(signalStart_), signal(signalStart), currentResult(true), historyResult(0,0)
{
  //  InitSignal();
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
  //std::cout<<tmpSignal<<std::endl;
  for(unsigned ibit=memsize; ibit>0; ibit--) {
    //    std::cout<<"ibit= "<<ibit<<" signal= "<<signal[ibit-1]<<std::endl;
    tmpSignal = 2*tmpSignal + signal[ibit-1];
  }
  //std::cout<<tmpSignal<<std::endl;
  return tmpSignal;
  //  return static_cast<unsigned long> (signal.to_ulong());
}

unsigned EGT::Market::GetMaxMemSize() const
{
  return static_cast<unsigned>(MEMMAX);
}

void EGT::Market::ShowSignal() const
{
  std::cout<<signal<<std::endl;
}
