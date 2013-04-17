/** \ingroup EGT */

/*! \file Player.h
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <math.h>
#include "Strategy.h"
#include "RandomDrand.h" // Random Number Generator
//#include "ParkMiller.h" // Random Number Generator
#include "MyUtils.h"

namespace EGT {

  class Player {

    typedef EGT::Strategy StrategyType;
    typedef RandomDrand RNGType;

    std::vector<StrategyType> strategies;
    unsigned numStrategy;
    unsigned memSize;
    unsigned long sigSize;
    unsigned prediction; // 1--A wins; 0--B wins
    unsigned selectedStrategy;
    unsigned long score;
    RNGType rng4Init;

    bool ScanStrategyScores(std::vector<double>& iPool);

  public:
    Player(unsigned numStrategy_, unsigned long memSize_, bool prediction_ = true, unsigned selectedStrategy_ = 0, long score_ = 0);
    Player();

    void InitializePlayer(const unsigned long& seed);
    void ChooseStrategy(const std::vector<double>& randoms);
    void ShowSelectedStrategy() const;
    void ShowPrediction() const;
    void Predict(const unsigned long& signal);
    void UpdateScore(const unsigned long& signal, const unsigned& currentResult);
    unsigned long GetScore() const;
    unsigned GetPrediction() const;
    unsigned GetMemSize() const;
  }; // Player

} // namespace EGT

#endif
