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

namespace EGT{

  class Strategy {

    std::bitset<SIZE> singleStrategy;
    unsigned long score;
    //    long seed;
    
  public:

    Strategy(unsigned long score_ = 0);

    void Initialize(const long& randomSeed);
    bool GetThisStrategyResult(const unsigned long& signal) const;
    void UpdateScore();
    unsigned long GetScore() const;

  }; // Strategy

} // namespace EGT

#endif
