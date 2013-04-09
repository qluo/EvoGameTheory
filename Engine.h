/** \ingroup EGT */

/*! \file Engine.h
 *
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "Player.h"
#include "Market.h"
#include "StatsGathererEGT.h"

namespace EGT {

  class Engine {
    
    std::vector<Player> players;
    long numPlayer;
    long numStrategy;
    std::ofstream fout;

    void WriteHeader();
    void WriteFooter();
    void PrintProgress(const char& mark='$');

  public:
    Engine();

    void Run();
    void Initialize();
    void PlayGame();
    void Finalize();

  }; // Engine

} // namespace EGT
