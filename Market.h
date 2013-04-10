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
    bool currentResult;
    std::pair<unsigned long, unsigned long> historyResult;
    
    //void Bin2Dec(const std::bitset<M>& b, long& n);

  public:
    Market(const std::string& signalStart_);

    void UpdateSignal(bool getResult);
    void ResetSignal();
    unsigned long GetSignal() const;
    
  }; // Market

} //namespace EGT

#endif
