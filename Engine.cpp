#include "Engine.h"
#include <algorithm>

EGT::Engine::Engine(const EGT::Parameters& params, EGT::Market& market_, std::vector<EGT::PlayerBase*>& playerPtr_, EGT::StatsGathererEGT& gatherer_) : playerPtr(playerPtr_), market(market_), gatherer(gatherer_), nPlayer(params.nPlayer), memSize(params.memSize), nStrategy(params.nStrategy), nPlayerTotal(0), nStrategyMax(0), stepMax(params.stepMAX), fout(params.outputFile.c_str()), rng(nStrategyMax, params.randomSeed[0])
{
  for(unsigned iSize=0; iSize<nPlayer.size(); iSize++) nPlayerTotal += nPlayer[iSize];
  myUtils::check(nPlayerTotal==playerPtr.size(), "EGT::Engine::Engine()");
  nStrategyMax = *(std::max_element(nStrategy.begin(), nStrategy.end()));
  //std::cout<<nStrategyMax<<std::endl;
  rng.ResetDimensionality(nStrategyMax);
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

}

void EGT::Engine::Initialize()
{
  std::cout<<"Engine.Initialize"<<std::endl;
  std::vector<double> randoms(nStrategyMax);

  for(IterPlayer it=playerPtr.begin();it!=playerPtr.end();it++) {
    //  for(unsigned long i=0; i<nPlayerTotal; i++) {
    rng.GetUniforms(randoms);
    (*it)->InitializeStrat(static_cast<unsigned long> (12345678*randoms[0]));
    //    playerPtr[i]->InitializeStrat(static_cast<unsigned long> (12345678*randoms[0]));
  }
  
}

void EGT::Engine::PlayGames()
{ 
  std::cout<<"Engine.PlayGames"<<std::endl;
  std::vector<double> randoms(nStrategyMax);
  for(unsigned long iStep=0; iStep<stepMax; iStep++) {
    for(IterPlayer it=playerPtr.begin();it!=playerPtr.end();it++) {
    //    for(unsigned long id=0; id<nPlayerTotal; id++) {
      rng.GetUniforms(randoms);
      (*it)->ChooseStrat(randoms);
      unsigned playerMemSize = (*it)->GetMemSize();
      (*it)->Predict(market.GetSignal(playerMemSize));
      gatherer.DumpOneResult((*it)->GetPrediction());
      //      playerPtr[id]->ChooseStrat(randoms);
      //      unsigned playerMemSize = playerPtr[id]->GetMemSize();
      //      playerPtr[id]->Predict(market.GetSignal(playerMemSize));
      //      gatherer.DumpOneResult(playerPtr[id]->GetPrediction());
    }

    bool currentResult = true;

    myUtils::check(gatherer.GetNumPlayerDone() == nPlayerTotal, "ERROR: Engine::PlayGames: gatherer.GetNumPlayerDone() != nPlayerTotal");
    currentResult = gatherer.Publish();
    UpdateAllInfo(currentResult);
    PrintProgress();
    //    market.ShowSignal();
  }
  std::cout<<std::endl;
}

void EGT::Engine::Finalize()
{
  std::cout<<"Engine.Finalize"<<std::endl;
  StatsGathererEGT::GathererType results = gatherer.GetResultsSoFar();  
  myUtils::check(stepMax == results.size(), "ERROR! EGT::Engine::Finalize()"); 
  // ------ output 1 ------ //
  fout<<"#ResultsHistory"<<std::endl;
  for(unsigned istep=0; istep<stepMax;istep++) {
    fout<<istep<<" "<<results[istep].first<<" "<<results[istep].second<<std::endl;
  }
  // ------ output 2 ------ //
  fout<<"#MemSizeVSScores"<<std::endl;
  for(IterPlayer it=playerPtr.begin();it!=playerPtr.end();it++) {
    fout<<(*it)->GetMemSize()<<" "<<(*it)->GetScore()<<std::endl;
  //  for(unsigned id=0; id<playerPtr.size(); id++) {
    //    fout<<playerPtr[id]->GetMemSize()<<" "<<playerPtr[id]->GetScore()<<std::endl;
  }
  // ----- to be implemented ---------- //
}

void EGT::Engine::UpdateAllInfo(bool currentResult)
{
  for(IterPlayer it=playerPtr.begin();it!=playerPtr.end();it++) {
  //  for(unsigned long id=0; id<nPlayerTotal; id++) {
    unsigned playerMemSize = (*it)->GetMemSize();
    (*it)->UpdateScore(market.GetSignal(playerMemSize), currentResult);
    //unsigned playerMemSize = playerPtr[id]->GetMemSize();
    //playerPtr[id]->UpdateScore(market.GetSignal(playerMemSize), currentResult);
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
