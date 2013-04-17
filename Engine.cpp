#include "Engine.h"
#include <algorithm>

EGT::Engine::Engine(const EGT::Parameters& params, EGT::Market& market_, std::vector<EGT::Player>& players_, EGT::StatsGathererEGT& gatherer_) : players(players_), market(market_), gatherer(gatherer_), nPlayer(params.nPlayer), memSize(params.memSize), nStrategy(params.nStrategy), nPlayerTotal(0), nStrategyMax(0), stepMax(params.stepMAX), fout(params.outputFile.c_str()), rng(nStrategyMax, params.randomSeed[0])
{
  for(unsigned iSize=0; iSize<nPlayer.size(); iSize++) nPlayerTotal += nPlayer[iSize];
  myUtils::error_testing(nPlayerTotal==players.size(), "EGT::Engine::Engine()");
  nStrategyMax = *(std::max_element(nStrategy.begin(), nStrategy.end()));
  rng.ResetDimensionality(nStrategyMax);
  //std::cout<<nPlayerTotal<<" "<<nStrategyMax<<std::endl;
}

void EGT::Engine::Run()
{
  WriteHeader();
  //-----------------
  Initialize();
  PlayGames();
  Finalize();
  //-----------------
  WriteFooter();

  //return 1;
}

void EGT::Engine::Initialize()
{
  std::cout<<"Engine.Initialize\n";
  std::vector<double> randoms(nStrategyMax);

  for(unsigned long i=0; i<nPlayerTotal; i++) {
    rng.GetUniforms(randoms);
    //std::cout<<randoms[i]<<std::endl;
    players[i].InitializePlayer(static_cast<unsigned long> (12345678*randoms[0]));
  }
  
}

void EGT::Engine::PlayGames()
{ 
  std::cout<<"Engine.PlayGames\n";
  std::vector<double> randoms(nStrategyMax);
  for(unsigned long iStep=0; iStep<stepMax; iStep++) {
    for(unsigned long id=0; id<nPlayerTotal; id++) {
      rng.GetUniforms(randoms);
      players[id].ChooseStrategy(randoms);
      unsigned playerMemSize = players[id].GetMemSize();
      //std::cout<<playerMemSize<<std::endl;
      players[id].Predict(market.GetSignal(playerMemSize));
      gatherer.DumpOneResult(players[id].GetPrediction());
    }

    bool currentResult = true;

    if(gatherer.GetNumPlayerDone() == nPlayerTotal) currentResult = gatherer.Publish();
    else std::cout<<"ERROR: "<<gatherer.GetNumPlayerDone()<<" "<<nPlayerTotal<<std::endl;
    //else throw std::runtime_error("EGT::Engine::PlayeGames gathering players information is not done!\n");
    //std::cout<<iStep<<" "<<currentResult<<std::endl;
    UpdateAllInfo(currentResult);
    //players[100].ShowPrediction();
    // players[100].ShowSelectedStrategy();
    PrintProgress();
  }
  std::cout<<std::endl;
}

void EGT::Engine::Finalize()
{
  std::cout<<"Engine.Finalize\n";
  StatsGathererEGT::GathererType results = gatherer.GetResultsSoFar();  
  if(stepMax == results.size() ) {
    fout<<"#ResultsHistory"<<std::endl;
    for(unsigned istep=0; istep<stepMax;istep++) {
      fout<<istep<<" "<<results[istep].first<<" "<<results[istep].second<<std::endl;
    }
  }
  else std::cout<<"Finalize Error!\n";
  //else throw std::runtime_error("EGT::Engine::Finalize() step is not done!");
  // ----- to be implemented ---------- //
}

void EGT::Engine::UpdateAllInfo(bool currentResult)
{
  for(unsigned long id=0; id<nPlayerTotal; id++) {
    unsigned playerMemSize = players[id].GetMemSize();
    players[id].UpdateScore(market.GetSignal(playerMemSize), currentResult);
  }
  market.UpdateSignal(currentResult);
  gatherer.UpdateResults();
}

void EGT::Engine::PrintProgress(const char &mark)
{
  std::cout<<mark;
  std::cout.flush();
}

void EGT::Engine::WriteHeader()
{
  fout<<"#This is simulation for Evolutionary Game Theory (EGT)\n";
  time_t t = time(0);
  fout<<ctime(&t);
  //fout<<params;
}

void EGT::Engine::WriteFooter()
{
  time_t t = time(0);
  fout<<ctime(&t);
  fout<<"#EOF\n";
}
