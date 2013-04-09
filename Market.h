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
#include "Constants.h"

namespace EGT {

  class Market {
    
    std::string signalStart;
    std::bitset<M> signal;
    std::pair<long,long> historyResult;
    
  public:
    Market();
      
    void UpdateSignal();
    void InitSignal();
    void SetSignal();
    long GetSignal() const;

  }; // Market

} //namespace EGT
