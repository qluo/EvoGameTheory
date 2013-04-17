#include "Player.h"

EGT::Player::Player(unsigned numStrategy_, unsigned long memSize_, bool prediction_, unsigned selectedStrategy_, long score_)
  : numStrategy(numStrategy_), memSize(memSize_), sigSize(pow(2,memSize)), prediction(prediction_), selectedStrategy(selectedStrategy_), score(score_), rng4Init(sigSize,0)
{
  for(unsigned is=0;is<numStrategy;is++) {
    strategies.push_back(*(new StrategyType(sigSize,0)));
  }
  myUtils::error_testing((strategies.size()==numStrategy), "ERROR! EGT::Player::Player()");
//strategies.resize(numStrategy);
}

EGT::Player::Player()
  : numStrategy(0), memSize(0), sigSize(0), prediction(0), selectedStrategy(0), score(0), rng4Init(sigSize,0)
{

}

void EGT::Player::InitializePlayer(const unsigned long& seed)
{
  rng4Init.SetSeed(seed);
  std::vector<double> randoms(sigSize);

  for(unsigned i=0; i<numStrategy; i++) {
    rng4Init.GetUniforms(randoms);
    strategies[i].Initialize(randoms); //static_cast<long> (12345678*randoms[i]));
  }
}

void EGT::Player::ChooseStrategy(const std::vector<double>& randoms)
{
  std::vector<double> iPool(numStrategy,0);
  myUtils::error_testing((randoms.size()>=numStrategy), "ERROR! EGT::Player::ChooseStrategy()");

  bool flag = ScanStrategyScores(iPool);
  unsigned iStrat = static_cast<unsigned>(randoms[0]*numStrategy);
  if(flag) {
    for(unsigned i=0; i<numStrategy; i++) iPool[i] *= randoms[i];
    
    for(unsigned i=0; i<numStrategy; i++) {
      if(iPool[i]>iPool[iStrat]) iStrat = i;
    }
  }

  selectedStrategy = iStrat;
}

void EGT::Player::Predict(const unsigned long& signal)
{
  prediction = strategies[selectedStrategy].GetThisStrategyResult(signal);
  //if(prediction == 1) return true;
  //else if(prediction == 0) return false;
  //else throw std::runtime_error ("ERROR: selectStrategy !!!");
}

void EGT::Player::UpdateScore(const unsigned long& signal, const unsigned& currentResult)
{
  if(currentResult == prediction) score++;
  for(unsigned i=0; i<numStrategy; i++) {
    strategies[i].UpdateScore(signal, currentResult);
  }
}

unsigned long EGT::Player::GetScore() const
{
  return score;
}

unsigned EGT::Player::GetPrediction() const
{
  return prediction;
}

bool EGT::Player::ScanStrategyScores(std::vector<double>& iPool)
{
  myUtils::error_testing((iPool.size()==numStrategy), "ERROR! EGT::Player::ScanStrategyScores");
  std::vector<unsigned long> stratScores(numStrategy);
  for(unsigned i=0; i<numStrategy; i++) stratScores[i]=strategies[i].GetScore();
  
  bool flag=false;
  unsigned iHigh = 0;
  for(unsigned i=0; i<numStrategy; i++) {
    if(stratScores[i]>stratScores[iHigh]) iHigh = i;
  }
  unsigned long highScore = stratScores[iHigh];
  
  for(unsigned i=0; i<numStrategy; i++) {
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

unsigned EGT::Player::GetMemSize() const
{
  return memSize;
}
