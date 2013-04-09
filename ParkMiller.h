#ifndef PARK_MILLER_H
#define PARK_MILLER_H
#include "RandomBase.h"

class ParkMiller
{
public:
	ParkMiller(long Seed = 1);
	long GetOneRandomInteger();
	void SetSeed(long Seed);
	
	static unsigned long Max();
	static unsigned long Min();

private:
	long Seed;
};

class RandomParkMiller : public RandomBase
{
public:
	RandomParkMiller(unsigned long Dimensionality, unsigned long Seed = 1);
	virtual RandomBase* clone() const;
	virtual void GetUniforms(std::vector<double>& variates);
	virtual void Skip(unsigned long NumberOfPaths);
	virtual void SetSeed(unsigned long Seed);
	virtual void Reset();
	virtual void ResetDimensionality(unsigned long NewDimensionality);

private:
	ParkMiller InnerGenerator;
	unsigned long InitialSeed;
	double Reciprocal;
};

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long Seed_)
: Seed(Seed_)
{
	if(Seed == 0) Seed = 1;
}

void ParkMiller::SetSeed(long Seed_)
{
	Seed = Seed_;
	if(Seed == 0) Seed = 1;
}

unsigned long ParkMiller::Max()
{
	return m-1;
}

unsigned long ParkMiller::Min()
{
	return 1;
}

long ParkMiller::GetOneRandomInteger()
{
	long k;
	k=Seed/q;
	Seed = a*(Seed - k*q) - r*k;
	if(Seed<0) Seed += m;
	
	return Seed;
}

RandomParkMiller::RandomParkMiller(unsigned long Dimensionality, unsigned long Seed)
: RandomBase(Dimensionality), InnerGenerator(Seed), InitialSeed(Seed)
{
	Reciprocal = 1/(1.0+InnerGenerator.Max());
}

RandomBase* RandomParkMiller::clone() const
{
	return new RandomParkMiller(*this);
}

void RandomParkMiller::GetUniforms(std::vector<double>& variates)
{
	for(unsigned long j=0; j<GetDimensionality(); j++)
		variates[j] = InnerGenerator.GetOneRandomInteger() * Reciprocal;
}

void RandomParkMiller::Skip(unsigned long NumberOfPaths)
{
	std::vector<double> tmp(GetDimensionality());
	for(unsigned long j=0; j<NumberOfPaths; j++) 
		GetUniforms(tmp);
}

void RandomParkMiller::SetSeed(unsigned long Seed)
{
	InitialSeed = Seed;
	InnerGenerator.SetSeed(Seed);
}

void RandomParkMiller::Reset()
{
	InnerGenerator.SetSeed(InitialSeed);
}

void RandomParkMiller::ResetDimensionality(unsigned long NewDimensionality)
{
	RandomBase::ResetDimensionality(NewDimensionality);
	InnerGenerator.SetSeed(InitialSeed);
}


#endif

