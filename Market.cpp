#include "Market.h"
//#include "MyUtils.h"

EGT::Market::Market(const std::string& signalStart_) : signalStart(signalStart_), signal(signalStart), currentResult(true), historyResult(0,0)
{
  //  InitSignal();
}

//void EGT::Market::InitSignal()
void EGT::Market::UpdateSignal(bool getResult)
{
  currentResult = getResult;
  signal <<= 1;

  if(signal == true) {
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
  std::bitset<M> signalTmp(signalStart);
  signal = signalTmp;
}

unsigned long EGT::Market::GetSignal() const
{
  return static_cast<unsigned long> (signal.to_ulong());
}
/*
void EGT::Market::Bin2Dec(const std::bitset<M>& b, long& n)
{

}
*/
