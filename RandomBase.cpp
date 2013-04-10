#include "RandomBase.h"
#include "Normals.h"
#include <cstdlib>

#if !defined(_MSC_VER)
using namespace std;
#endif

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

