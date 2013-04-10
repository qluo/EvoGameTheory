/** \ingroup EGT */

/*! \file Player.h
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "Constants.h"
#include "Strategy.h"

namespace EGT {

  class Player {

    typedef typename EGT::Strategy StrategyType;
    std::vector<StrategyType> strategies;

    bool prediction; // 1--A wins; 0--B wins
    unsigned selectedStrategy;
    unsigned long score;

    bool ScanStrategyScores(std::vector<double>& iPool);

  public:
    Player(bool prediction_ = true, unsigned selectedStrategy_ = 0, long score_ = 0);

    void InitializePlayer(const long seed);
    void ChooseStrategy(const long& randomSeed);
    void Predict(const unsigned long& signal);
    void UpdateScore(bool currentResult);
    unsigned long GetScore() const;
    bool GetPrediction() const;
    
  }; // Player

} // namespace EGT

#endif
