/*	Evonomics theory --- Evolutionary Game Theory (EGT)
 *	by Q. Luo
 *	Date: Apr 8, 2013
 *	Platform: linux
 *	Model: Physica A 246 (1997) 407-418 
 */

#include "SimpleReader.h"
#include "Parameters.h"
#include "Engine.h"
#include "Player.h"
#include "Market.h"
#include "StatsGathererEGT.h"
#include "MyUtils.h"

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

  MarketType& market = MarketType::Instance(params.initSignal);
  GathererType gatherer(0);
  
  std::vector<PlayerType> players;

  // --- initialize players --- //
  unsigned long totalPlayer = 0;
  for(unsigned ik=0; ik<params.nPlayer.size(); ik++) {
    for(unsigned ip=0;ip<params.nPlayer[ik];ip++) {
      players.push_back(*(new PlayerType(params.nStrategy[ik], params.memSize[ik])));
      totalPlayer++;
    }
  }
  myUtils::error_testing((players.size()==totalPlayer), "ERROR! Total Number of Players");

  EngineType engine(params,market,players,gatherer);
  engine.Run();

}

/* ####### End of main.cpp ######## */

