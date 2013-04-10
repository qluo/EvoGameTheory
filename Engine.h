/** \ingroup EGT */

/*! \file Engine.h
 *
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <fstream>
//#include <iostream>
#include "Parameters.h"
#include "Player.h"
#include "Market.h"
#include "StatsGathererEGT.h"
#include "ParkMiller.h"
#include "MyUtils.h"


namespace EGT {

  class Engine {
    
    typedef RandomParkMiller RNGType;

    //Parameters& parameters;
    unsigned long nPlayer;
    unsigned long stepMax;
    std::ofstream fout;
    RNGType rng;

    std::vector<EGT::Player> players;
    Market market;
    StatsGathererEGT gatherer;
    
    void WriteHeader();
    void WriteFooter();
    void UpdateAllInfo(bool currentResult);
    void PrintProgress(const char &mark='$');

  public:

    Engine(const Parameters& params);

    void Run();
    void Initialize();
    void PlayGames();
    void Finalize();

  }; // Engine

} // namespace EGT

#endif
