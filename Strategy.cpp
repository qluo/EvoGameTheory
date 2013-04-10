#include "Strategy.h"
#include "ParkMiller.h" // Random Number Generator

typedef RandomParkMiller RNGType;

EGT::Strategy::Strategy(unsigned long score_) : score(score_)
{
  //Initialize();
}

void EGT::Strategy::Initialize(const long& randomSeed)
{
  RNGType rng(SIZE, randomSeed);
  std::vector<double> randoms(SIZE);
  
  rng.GetUniforms(randoms);
  for(unsigned ibit=0; ibit<SIZE; ibit++) {
    if(randoms[ibit]<0.5) singleStrategy.set(ibit);
    else singleStrategy.reset(ibit);
  }
  
}

bool EGT::Strategy::GetThisStrategyResult(const unsigned long& signal) const
{
  if(singleStrategy[signal] == 1) return true;
  else return false;
}

void EGT::Strategy::UpdateScore()
{
  score++;
}

unsigned long EGT::Strategy::GetScore() const
{
  return score;
}
