/** \ingroup EGT */

/*! \file Strategy.h
 *
 */

#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>
#include <bitset>
#include <iostream>
#include "Constants.h"
#include "RandomDrand.h" // Random Number Generator
//#include "ParkMiller.h" // Random Number Generator

namespace EGT{

  class Strategy {

    std::bitset<SIZE> singleStrategy;
    unsigned long score;
    
  public:

    Strategy(unsigned long score_ = 0);

    void Initialize(const std::vector<double>& randoms);
    bool GetThisStrategyResult(const unsigned long& signal) const;
    void UpdateScore(const unsigned long& signal, const bool& currentResult);
    unsigned long GetScore() const;

  }; // Strategy

} // namespace EGT

#endif
