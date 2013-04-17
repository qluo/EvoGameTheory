/*	Evonomics theory --- Evolutionary Game Theory (EGT)
 *	by Q. Luo
 *	Date: Apr 8, 2013
 *	Platform: linux
 *	Model: Physica A 246 (1997) 407-418 
 */

#include "SimpleReader.h"
//#include "Constants.h"
#include "Parameters.h"
#include "Engine.h"
#include "Player.h"
#include "Market.h"
#include "StatsGathererEGT.h"

typedef EGT::Parameters ParamsType;
typedef EGT::Engine EngineType;
typedef EGT::Market MarketType;
typedef EGT::StatsGathererEGT GathererType;
typedef EGT::Player PlayerType;

int main(int argc,char *argv[])
{
  ParamsType params;
  Dmrg::SimpleReader reader(argv[1]);
  
  std::cout<<"Loading"<<std::endl;
  reader.load(params);

  MarketType market(params.initSignal);
  GathererType gatherer(0);
  
  std::vector<PlayerType> players;

  // --- initialize players --- //
  for(unsigned ip=0;ip<params.nPlayer[0];ip++) {
    //    PlayerType tmpPlayer(params.nStrategy[0], params.memSize[0]);
    players.push_back(*(new PlayerType(params.nStrategy[0], params.memSize[0])));
  }
  
  EngineType engine(params,market,players,gatherer);
  engine.Run();

}

/* ####### End of main.cpp ######## */

