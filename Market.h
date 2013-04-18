/** \ingroup EGT */

/*! \file Market.h
 *
 * System Signal containing M bits
 *     -------------------------
 *     |   1 -- A win, B lose  |
 *     |   0 -- A lose, B win  |
 *     -------------------------
 */

#ifndef MARKET_H
#define MARKET_H

#include <bitset>
#include <iostream>
#include "MyUtils.h"

namespace EGT {

  class Market {

    enum {MEMMAX=20};

    std::string signalStart;
    std::bitset<MEMMAX> signal;
    unsigned currentResult;
    std::pair<unsigned long, unsigned long> historyResult;
    
  public:
    Market(const std::string& signalStart_);

    void UpdateSignal(unsigned getResult);
    void ResetSignal();
    unsigned long GetSignal(unsigned memsize) const;
    unsigned GetMaxMemSize() const;
    void ShowSignal() const;
    
  }; // Market

} //namespace EGT

#endif
