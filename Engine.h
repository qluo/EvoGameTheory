/** \ingroup EGT */

/*! \file Engine.h
 *
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <fstream>
#include <vector>
#include "Parameters.h"
#include "PlayerBase.h"
#include "Market.h"
#include "StatsGathererEGT.h"
#include "RandomNumRec.h"
//#include "ParkMiller.h"
//#include "RandomDrand.h"
#include "MyUtils.h"

namespace EGT {

  class Engine {
    
    typedef RandomNumRec RNGType;
    typedef std::vector<EGT::PlayerBase*>::iterator IterPlayer;

    std::vector<EGT::PlayerBase*>& playerPtr;
    Market& market;
    StatsGathererEGT& gatherer;

    std::vector<unsigned long> nPlayer;
    std::vector<unsigned> memSize;
    std::vector<unsigned> nStrategy;
    
    unsigned long nPlayerTotal;
    unsigned nStrategyMax;
    unsigned long stepMax;
    std::ofstream fout;
    RNGType rng;
    
    void WriteHeader();
    void WriteFooter();
    void UpdateAllInfo(bool currentResult);
    void PrintProgress(const char &mark='$');

  public:

    Engine(const EGT::Parameters& params, EGT::Market& market_, std::vector<EGT::PlayerBase*>& playerPtr_, EGT::StatsGathererEGT& gatherer_);

    void Run();
    void Initialize();
    void PlayGames();
    void Finalize();

  }; // Engine

} // namespace EGT

#endif
