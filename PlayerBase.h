/** \ingroup EGT */

/*! \file PlayerBase.h
 */

#ifndef PLAYER_BASE_H
#define PLAYER_BASE_H

#include <vector>

namespace EGT {

  class PlayerBase {

  public:
    PlayerBase() {}
    virtual ~PlayerBase() {}

    virtual void InitializeStrat(const unsigned long& seed) = 0;
    virtual void ChooseStrat(const std::vector<double>& randoms) = 0;
    virtual void Predict(const unsigned long& signal) = 0;
    virtual void UpdateScore(const unsigned long& signal, const unsigned& currentResult) = 0;
    
    virtual unsigned long GetScore() const = 0;
    virtual unsigned GetPrediction() const = 0;
    virtual unsigned GetMemSize() const = 0;
    virtual void ShowSelectedStrat() const = 0;
    virtual void ShowPrediction() const = 0;

  private:

  }; // PlayerBase

} // namespace EGT

#endif
