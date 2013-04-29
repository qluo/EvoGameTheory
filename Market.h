/** \ingroup EGT */

/*! \file Market.h
 *
 * Singleton (only one market guaranteed)
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

    //    static Market theMarket;

    std::string signalStart;
    std::bitset<MEMMAX> signal;
    unsigned currentResult;
    std::pair<unsigned long, unsigned long> historyResult;    

  protected:
    Market(); //Disallowed
    Market(const Market& ); //Disallowed
    Market& operator = (const Market&); //Disallowed
    Market(const std::string& signalStart_);

  public:

    static Market& Instance(const std::string& signalStart_);

    void UpdateSignal(unsigned getResult);
    void ResetSignal();
    unsigned long GetSignal(unsigned memsize) const;
    unsigned GetMaxMemSize() const;
    void ShowSignal() const;
    
  }; // Market

} //namespace EGT

#endif
