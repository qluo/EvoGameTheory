/** \ingroup EGT */

/*! \file Player.h
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

//#include <vector>
//#include <bitset>
#include "Constants.h"
#include "Strategy.h"

namespace EGT {

  class Player {

    typedef EGT::Strategy StrategyType;
    // std::vector< std::bitset<SIZE> > strategy;
    StrategyType strategy;
    long numStrategy;
    bool prediction; // 1--A wins; 0--B wins
    unsigned selectedStrategy;
    long score;

  public:
    Player();

    //void ProcessInfo(long signal);
    void ChooseStrategy();
    bool Predict(long signal) const;
    void UpdateScores();
    
  }; // Player

} // namespace EGT

#endif
