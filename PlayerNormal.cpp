#include "PlayerNormal.h"
#include "MyUtils.h"

#include <iostream>
#include <math.h>
#include <algorithm>

EGT::PlayerNormal::PlayerNormal(unsigned numStrat_, unsigned long memSize_, bool prediction_, unsigned selectedStrat_, long score_)
  : numStrat(numStrat_), memSize(memSize_), sigSize(pow(2,memSize)), prediction(prediction_), selectedStrat(selectedStrat_), score(score_), rng4Init(sigSize,0)
{
  for(unsigned is=0;is<numStrat;is++) {
    strats.push_back( StratType(sigSize,0) );
  }
  myUtils::check((strats.size()==numStrat), "ERROR! EGT::Player::Player()");
}

EGT::PlayerNormal::PlayerNormal()
  : numStrat(0), memSize(0), sigSize(0), prediction(0), selectedStrat(0), score(0), rng4Init(sigSize,0)
{

}

void EGT::PlayerNormal::InitializeStrat(const unsigned long& seed)
{
  rng4Init.SetSeed(seed);
  std::vector<double> randoms(sigSize);

  for(IterStrat its=strats.begin(); its!=strats.end(); its++) {
    rng4Init.GetUniforms(randoms);
    its->Initialize(randoms);
  }
}

void EGT::PlayerNormal::ChooseStrat(const std::vector<double>& randoms)
{
  std::vector<double> iPool(numStrat,0);
  myUtils::check((randoms.size()>=numStrat), "ERROR! EGT::Player::ChooseStrat()");

  bool flag = ScanStratScores(iPool);
  unsigned iStrat = static_cast<unsigned>(randoms[0]*numStrat);
  if(flag) {
    for(unsigned i=0; i<numStrat; i++) iPool[i] *= randoms[i];
    
    for(unsigned i=0; i<numStrat; i++) {
      if(iPool[i]>iPool[iStrat]) iStrat = i;
    }
  }

  selectedStrat = iStrat;
}

void EGT::PlayerNormal::Predict(const unsigned long& signal)
{
  prediction = strats[selectedStrat].GetThisStrategyResult(signal);
}

void EGT::PlayerNormal::UpdateScore(const unsigned long& signal, const unsigned& currentResult)
{
  if(currentResult == prediction) score++;
  for(IterStrat its=strats.begin(); its!=strats.end(); its++) {
    its->UpdateScore(signal, currentResult);
  }
}

unsigned long EGT::PlayerNormal::GetScore() const
{
  return score;
}

unsigned EGT::PlayerNormal::GetPrediction() const
{
  return prediction;
}

bool EGT::PlayerNormal::ScanStratScores(std::vector<double>& iPool) const
{
  bool flag=false;
  myUtils::check((iPool.size()==numStrat), "ERROR! EGT::Player::ScanStratScores");

  IterConstStrat itsHigh = std::max_element(strats.begin(), strats.end());
  unsigned long highScore = (*itsHigh).GetScore();
  
  for(unsigned i=0; i<numStrat; i++) {
    if(strats[i].GetScore() == highScore) {
      iPool[i] = 1;
      flag = true;
    }
    else if (strats[i].GetScore() < highScore) iPool[i] = 0;
  }
			
  return flag;
}

void EGT::PlayerNormal::ShowSelectedStrat() const
{
  std::cout<<selectedStrat;
}

void EGT::PlayerNormal::ShowPrediction() const
{
  std::cout<<prediction;
}

unsigned EGT::PlayerNormal::GetMemSize() const
{
  return memSize;
}

//--- Factory method ---//
EGT::PlayerBase* EGT::PlayerNormal::Factory::create(const unsigned& numStrat, const unsigned long& memSize)
{
  return new PlayerNormal(numStrat, memSize);
}
