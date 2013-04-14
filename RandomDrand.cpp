#include "RandomDrand.h"
#include <time.h>

RandomDrand::RandomDrand(unsigned long Dimensionality, unsigned long Seed)
: RandomBase(Dimensionality), InitialSeed(Seed)
{
  if(InitialSeed<1) InitialSeed = time(0);
  srand48(InitialSeed);
}

RandomBase* RandomDrand::clone() const
{
  return new RandomDrand(*this);
}

void RandomDrand::GetUniforms(std::vector<double>& variates)
{
  for(unsigned long j=0; j<GetDimensionality(); j++)
    variates[j] = drand48();
}

void RandomDrand::Skip(unsigned long NumberOfPaths)
{
  std::vector<double> tmp(GetDimensionality());
  for(unsigned long j=0; j<NumberOfPaths; j++) 
    GetUniforms(tmp);
}

void RandomDrand::SetSeed(unsigned long Seed)
{
  InitialSeed = Seed;
  srand48(Seed);
}

void RandomDrand::Reset()
{
  srand48(InitialSeed);
}

void RandomDrand::ResetDimensionality(unsigned long NewDimensionality)
{
  RandomBase::ResetDimensionality(NewDimensionality);
  srand48(InitialSeed);
}






