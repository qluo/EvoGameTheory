#include "Player.h"

EGT::Player::Player(bool prediction_, unsigned selectedStrategy_, long score_) : prediction(prediction_), selectedStrategy(selectedStrategy_), score(score_), rng4Init(SIZE,0)
										 // rng4Choose(NUMSTRAT,0),
{
  strategies.resize(NUMSTRAT);
}

void EGT::Player::ChooseStrategy(const std::vector<double>& randoms)
{
  std::vector<double> iPool(NUMSTRAT,0);
  if(randoms.size() != NUMSTRAT) std::cout<<"ERROR! EGT::Player::ChooseStrategy\n";
  //rng4Choose.GetUniforms(randoms);

  bool flag = ScanStrategyScores(iPool);
  unsigned iStrat = static_cast<unsigned>(randoms[0]*NUMSTRAT);;
  if(flag) {
    for(unsigned i=0; i<NUMSTRAT; i++) iPool[i] *= randoms[i];
    
    for(unsigned i=0; i<NUMSTRAT; i++) {
      if(iPool[i]>iPool[iStrat]) iStrat = i;
    }
  }

  selectedStrategy = iStrat;

  //return true;
}

void EGT::Player::Predict(const unsigned long& signal)
{
  prediction = strategies[selectedStrategy].GetThisStrategyResult(signal);
  //if(prediction == 1) return true;
  //else if(prediction == 0) return false;
  //else throw std::runtime_error ("ERROR: selectStrategy !!!");
}

void EGT::Player::UpdateScore(const unsigned long& signal, const bool& currentResult)
{
  if(currentResult == prediction) score++;
  for(unsigned i=0; i<NUMSTRAT; i++) {
    strategies[i].UpdateScore(signal, currentResult);
  }
}

unsigned long EGT::Player::GetScore() const
{
  return score;
}

bool EGT::Player::GetPrediction() const
{
  return prediction;
}

void EGT::Player::InitializePlayer(const unsigned long& seed)
{
  rng4Init.SetSeed(seed);
  //  rng4Choose.SetSeed(seed2);
  std::vector<double> randoms(SIZE);

  for(unsigned i=0; i<NUMSTRAT; i++) {
    rng4Init.GetUniforms(randoms);
    strategies[i].Initialize(randoms); //static_cast<long> (12345678*randoms[i]));
  }
  //std::cout<<"test"<<std::endl;
}

bool EGT::Player::ScanStrategyScores(std::vector<double>& iPool)
{
  std::vector<unsigned long> stratScores(NUMSTRAT);
  for(unsigned i=0; i<NUMSTRAT; i++) stratScores[i]=strategies[i].GetScore();
  
  bool flag=false;
  unsigned iHigh = 0;
  for(unsigned i=0; i<NUMSTRAT; i++) {
    if(stratScores[i]>stratScores[iHigh]) iHigh = i;
  }
  unsigned long highScore = stratScores[iHigh];
  
  for(unsigned i=0; i<NUMSTRAT; i++) {
    if(stratScores[i] == highScore) {
      iPool[i] = 1;
      flag = true;
    }
    else if (stratScores[i] < highScore) iPool[i] = 0;
    //else throw std::runtime_error ("ERROR: EGT::Player::ScanStrategyScores() !!!");
  }
			
  return flag;
}

void EGT::Player::ShowSelectedStrategy() const
{
  std::cout<<selectedStrategy;
}

void EGT::Player::ShowPrediction() const
{
  std::cout<<prediction;
}
