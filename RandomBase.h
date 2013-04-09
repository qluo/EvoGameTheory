#ifndef RANDOM_BASE_H
#define RANDOM_BASE_H

//#include "Array.h"
#include <vector>

#include "Normals.h"
#include <cstdlib>

class RandomBase
{
public:
	RandomBase(unsigned long Dimensionality);

	inline unsigned long GetDimensionality() const;

	virtual RandomBase* clone() const=0;
	virtual void GetUniforms(std::vector<double>& variates) =0;
	virtual void Skip(unsigned long numberOfPaths) =0;
	virtual void SetSeed(unsigned long Seed) =0;
	virtual void Reset() =0;

	virtual void GetGaussians(std::vector<double>& variates);
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	unsigned long Dimensionality;
	
};

unsigned long RandomBase::GetDimensionality() const
{
	return Dimensionality;
}

void RandomBase::GetGaussians(std::vector<double>& variates)
{
	GetUniforms(variates);
	for(unsigned long i=0; i<Dimensionality; i++)
	{
		double x=variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}
}

void RandomBase::ResetDimensionality(unsigned long NewDimensionality)
{
	Dimensionality = NewDimensionality;
}

RandomBase::RandomBase(unsigned long Dimensionality_)
: Dimensionality(Dimensionality_)
{
}

#endif
