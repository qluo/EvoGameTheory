#include "Strategy.h"

typedef RandomDrand RNGType;

EGT::Strategy::Strategy(unsigned long size_, unsigned long score_) : size(size_), score(score_)
{
  singleStrategy.resize(size);
}

void EGT::Strategy::Initialize(const std::vector<double>& randoms)
{
  myUtils::error_testing((randoms.size()==size), "ERROR! EGT::Strategy::Initialize()");

  for(unsigned ibit=0; ibit<size; ibit++) {
    if(randoms[ibit]<=0.5) singleStrategy[ibit]=1;
    else singleStrategy[ibit]=0;
  }
  
}

unsigned EGT::Strategy::GetThisStrategyResult(const unsigned long& signal) const
{
  myUtils::error_testing((signal<size), "ERROR! EGT::Strategy::GetThisStrategyResult()");

  if(singleStrategy[signal] == 1) return true;
  else return false;
}

void EGT::Strategy::UpdateScore(const unsigned long& signal, const unsigned& currentResult)
{
  myUtils::error_testing( (signal < size) && (currentResult<2), "ERROR: EGT::Strategy::UpdateScore()");
  if(singleStrategy[signal] == currentResult) score++;
}

unsigned long EGT::Strategy::GetScore() const
{
  return score;
}
