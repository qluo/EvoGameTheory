#ifndef RANDOM_NUM_REC_H
#define RANDOM_NUM_REC_H
#include "RandomBase.h"

/* RandomNumRec.h 
 * Random Number Generator
 * from Numerical Recipes (3rd Edition), Chapter 7.1.7, Page 357
 */

class Ranlim32
{
 public:
  typedef unsigned int Uint;
 Ranlim32(Uint j) : v(2244614371U), w1(521288629U), w2(362436069U) 
    {
      u = j ^ v; int32();
      v = u; int32();
     }
  inline Uint int32() {
    u = u*2891336453U + 1640531513U;
    v ^= v >> 13; v ^= v << 17; v ^= v >> 5;
    w1 = 33378 * (w1 & 0xffff) + (w1>>16);
    w2 = 57225 * (w2 & 0xffff) + (w2>>16);
    Uint x = u^(u<<9); x ^= x>>17; x ^= x<<6;
    Uint y = w1^(w1<<17); y ^= y>>15; y ^= y<<5;
    return (x+v)^(y+w2);
  }
  // Uniform on (0,1). 32 bits of precision
  inline double doub() { return 2.32830643653869629E-10 * int32(); }
  // Slow version for full precision
  inline double truedoub() { return 2.32830643653869629E-10 * (int32() + 2.32830643653869629E-10*int32()); }
 private:
  unsigned long u, v, w1, w2;
};

class RandomNumRec : public RandomBase
{

public:
  RandomNumRec(unsigned long Dimensionality, unsigned long Seed = 1);

  virtual RandomBase* clone() const;
  virtual void GetUniforms(std::vector<double>& variates);
  virtual void Skip(unsigned long NumberOfPaths);
  virtual void SetSeed(unsigned long Seed);
  virtual void Reset();
  virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
  unsigned long InitialSeed;
  Ranlim32 randInner;
};

#endif
