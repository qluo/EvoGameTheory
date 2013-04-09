/** \ingroup EGT */

/*! \file Strategy.h
 *
 */

#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>
#include <bitset>
#include "Constants.h"

namespace EGT{

  class Strategy {

    std::bitset<SIZE> singleStrategy;
    unsigned long score;
    long seed;
    
  public:

    Strategy(long randomSeed = 0);

    void InitializePool();
    bool GetThisStrategyResult(const long& signal) const;
    void UpdateScore();
    unsigned long GetScore() const;

  }; // Strategy

} // namespace EGT

#endif
