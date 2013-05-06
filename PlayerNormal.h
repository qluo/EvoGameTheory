/** \ingroup EGT */

/*! \file PlayerNormal.h
 *
 */

#ifndef PLAYER_NORMAL_H
#define PLAYER_NORMAL_H

#include "PlayerBase.h"
#include "PlayerFactory.h"
#include "Strategy.h"
#include "RandomNumRec.h"
//#include "RandomDrand.h" // Random Number Generator
//#include "ParkMiller.h" // Random Number Generator
#include <vector>

namespace EGT {

  class PlayerNormal : public PlayerBase {
  public:
    typedef EGT::Strategy StratType;
    typedef std::vector<StratType>::iterator IterStrat;
    typedef std::vector<StratType>::const_iterator IterConstStrat;
    typedef RandomNumRec RNGType;

    PlayerNormal(unsigned numStrat_, unsigned long memSize_, bool prediction_ = true, unsigned selectedStrat_ = 0, long score_ = 0);
    PlayerNormal();
    ~PlayerNormal() {}
 
    void InitializeStrat(const unsigned long& seed);
    void ChooseStrat(const std::vector<double>& randoms);
    void Predict(const unsigned long& signal);
    void UpdateScore(const unsigned long& signal, const unsigned& currentResult);
    unsigned long GetScore() const;
    unsigned GetPrediction() const;
    unsigned GetMemSize() const;
    void ShowSelectedStrat() const;
    void ShowPrediction() const;

  private:

    std::vector<StratType> strats;
    unsigned numStrat;
    unsigned memSize;
    unsigned long sigSize;
    unsigned prediction; // 1--A wins; 0--B wins
    unsigned selectedStrat;
    unsigned long score;
    RNGType rng4Init;

    bool ScanStratScores(std::vector<double>& iPool) const;

    //--- Factory method ---//
    friend class PlayerFactoryInitializer;
    class Factory;
    friend class Factory;
    class Factory : public PlayerFactory 
    {
    public:
      PlayerBase* create(const unsigned& numStrat, const unsigned long& memSize);
      friend class PlayerFactoryInitializer;
    }; // Factory
    
  }; // PlayerNormal

} // namespace EGT

#endif
