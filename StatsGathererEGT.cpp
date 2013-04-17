#include "StatsGathererEGT.h"

EGT::StatsGathererEGT::StatsGathererEGT(unsigned long stepDone_) : sums(0,0), stepDone(stepDone_)
{

}

void EGT::StatsGathererEGT::DumpOneResult(bool result)
{
  if(result) sums.first++;
  else sums.second++;
}

void EGT::StatsGathererEGT::UpdateResults()
{
  stepDone++;
  hisResults.push_back(sums);
  sums.first=0;
  sums.second=0;
}

EGT::StatsGathererEGT::GathererType EGT::StatsGathererEGT::GetResultsSoFar() const
{
  return hisResults;
}

bool EGT::StatsGathererEGT::Publish()
{
  if(sums.first<sums.second) return true;
  else return false;
  //UpdateResults();
}

EGT::StatsGathererEGT* EGT::StatsGathererEGT::clone() const
{
  return new StatsGathererEGT(*this);
}
