/** \ingroup EGT */

/*! \file Strategy.h
 *
 */

#ifndef STRATEGY_H
#define STRATEGY_H
#include <vector>
#include <iostream>
#include "MyUtils.h"
#include "RandomDrand.h" // Random Number Generator
//#include "ParkMiller.h" // Random Number Generator

namespace EGT{

  class Strategy {

    std::vector<unsigned> singleStrategy;
    unsigned long size;
    unsigned long score;
    
  public:

    Strategy(unsigned long size_ = 0, unsigned long score_ = 0);

    void Initialize(const std::vector<double>& randoms);
    unsigned GetThisStrategyResult(const unsigned long& signal) const;
    void UpdateScore(const unsigned long& signal, const unsigned& currentResult);
    unsigned long GetScore() const;

    friend bool operator < (const Strategy& left, const Strategy& right);
  }; // Strategy

  bool operator < (const Strategy& left, const Strategy& right);

} // namespace EGT

#endif
