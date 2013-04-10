#include "Engine.h"
//#include "Constants.h"

EGT::Engine::Engine(const EGT::Parameters& params) : nPlayer(params.nPlayer), stepMax(params.stepMAX), fout(params.outputFile.c_str()), rng(nPlayer, params.randomSeed[0]), players(nPlayer), market(params.initSignal)
{

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
  std::vector<double> randoms(nPlayer);
  rng.GetUniforms(randoms);
  for(unsigned long i=0; i<nPlayer; i++) {
    //std::cout<<randoms[i]<<std::endl;
    players[i].InitializePlayer(static_cast<long>(randoms[i]*12345678));
  }
  
}

void EGT::Engine::PlayGames()
{ 
  std::cout<<"Engine.PlayGames\n";
  std::vector<double> randSeeds(nPlayer);
  for(unsigned long iStep=0; iStep<stepMax; iStep++) {
    for(unsigned long id=0; id<nPlayer; id++) {
      rng.GetUniforms(randSeeds);
      players[id].ChooseStrategy(static_cast<long>(randSeeds[id]*12345678));
      players[id].Predict(market.GetSignal());
      gatherer.DumpOneResult(players[id].GetPrediction());
    }

    bool currentResult = true;

    if(gatherer.GetNumPlayerDone() == nPlayer) currentResult = gatherer.Publish();
    else std::cout<<"ERROR: "<<gatherer.GetNumPlayerDone()<<" "<<nPlayer<<std::endl;
    //else throw std::runtime_error("EGT::Engine::PlayeGames gathering players information is not done!\n");
    std::cout<<iStep<<" "<<currentResult<<std::endl;
    UpdateAllInfo(currentResult);
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
    fout<<results;
  }
  else std::cout<<"Finalize Error!\n";
  //else throw std::runtime_error("EGT::Engine::Finalize() step is not done!");
  // ----- to be implemented ---------- //
}

void EGT::Engine::UpdateAllInfo(bool currentResult)
{
  market.UpdateSignal(currentResult);
  for(unsigned long id=0; id<nPlayer; id++) {
    players[id].UpdateScore(currentResult);
  }
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
