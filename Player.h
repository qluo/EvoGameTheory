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
#include "RandomDrand.h" // Random Number Generator
//#include "ParkMiller.h" // Random Number Generator

namespace EGT {

  class Player {

    typedef EGT::Strategy StrategyType;
    std::vector<StrategyType> strategies;
    typedef RandomDrand RNGType;

    bool prediction; // 1--A wins; 0--B wins
    unsigned selectedStrategy;
    unsigned long score;
    //RNGType rng4Choose;
    RNGType rng4Init;

    bool ScanStrategyScores(std::vector<double>& iPool);

  public:
    Player(bool prediction_ = true, unsigned selectedStrategy_ = 0, long score_ = 0);

    void InitializePlayer(const unsigned long& seed);
    void ChooseStrategy(const std::vector<double>& randoms);
    void ShowSelectedStrategy() const;
    void ShowPrediction() const;
    void Predict(const unsigned long& signal);
    void UpdateScore(const unsigned long& signal, const bool& currentResult);
    unsigned long GetScore() const;
    bool GetPrediction() const;
    
  }; // Player

} // namespace EGT

#endif
