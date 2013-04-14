#ifndef RANDOM_DRAND_H
#define RANDOM_DRAND_H
#include <stdlib.h>
#include "RandomBase.h"

/* Random Number Generator 
   based on drand48() in stdlib.h
*/

class RandomDrand : public RandomBase
{

public:
  RandomDrand(unsigned long Dimensionality, unsigned long Seed = 1);
  virtual RandomBase* clone() const;
  virtual void GetUniforms(std::vector<double>& variates);
  virtual void Skip(unsigned long NumberOfPaths);
  virtual void SetSeed(unsigned long Seed);
  virtual void Reset();
  virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
  unsigned long InitialSeed;
};

#endif
