#include "Player.h"
#include "ParkMiller.h" // Random Number Generator

typedef RandomParkMiller RNGType;

EGT::Player::Player(bool prediction_, unsigned selectedStrategy_, long score_) : prediction(prediction_), selectedStrategy(selectedStrategy_), score(score_)
{
  strategies.resize(NUMSTRAT);
}

void EGT::Player::ChooseStrategy(const long& randomSeed)
{
  std::vector<double> iPool(NUMSTRAT,0);
  RNGType rng(NUMSTRAT, randomSeed);
  std::vector<double> randoms(NUMSTRAT);
  rng.GetUniforms(randoms);

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

void EGT::Player::UpdateScore(bool currentResult)
{
  if(currentResult == prediction) {
    score++;
    strategies[selectedStrategy].UpdateScore();
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

void EGT::Player::InitializePlayer(const long seed)
{
  
  RNGType rng(NUMSTRAT, seed);
  std::vector<double> randoms(NUMSTRAT);
  rng.GetUniforms(randoms);

  for(unsigned i=0; i<NUMSTRAT; i++) {
    strategies[i].Initialize(static_cast<long> (12345678*randoms[i]));
  }
  
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
