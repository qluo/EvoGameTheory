#include "RandomNumRec.h"
#include <time.h>

RandomNumRec::RandomNumRec(unsigned long Dimensionality, unsigned long Seed)
  : RandomBase(Dimensionality), InitialSeed(Seed<1 ? time(0) : Seed), randInner(InitialSeed)
{
  //  if(InitialSeed<1) InitialSeed = time(0);
}

RandomBase* RandomNumRec::clone() const
{
  return new RandomNumRec(*this);
}

void RandomNumRec::GetUniforms(std::vector<double>& variates)
{
  for(unsigned long j=0; j<GetDimensionality(); j++)
    variates[j] = randInner.doub();
}

void RandomNumRec::Skip(unsigned long NumberOfPaths)
{
  std::vector<double> tmp(GetDimensionality());
  for(unsigned long j=0; j<NumberOfPaths; j++) 
    GetUniforms(tmp);
}

void RandomNumRec::SetSeed(unsigned long Seed)
{
  InitialSeed = (Seed<1 ? time(0) : Seed);
  Reset();
  //randInner = Ranlim32(InitialSeed);
}

void RandomNumRec::Reset()
{
  randInner = Ranlim32(InitialSeed);
}

void RandomNumRec::ResetDimensionality(unsigned long NewDimensionality)
{
  RandomBase::ResetDimensionality(NewDimensionality);
  Reset();
  //randInner = Ranlim32(InitialSeed);
}
