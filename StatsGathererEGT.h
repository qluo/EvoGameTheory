#ifndef STATS_GATHERER_EGT_H
#define STATS_GATHERER_EGT_H

#include <utility>
#include <vector>

namespace EGT {

  class StatsGathererEGT
  {
  public:

    typedef std::pair<unsigned long, unsigned long> PairType;
    typedef std::vector< PairType > GathererType;

    StatsGathererEGT();
    void DumpOneResult(bool result);
    void UpdateResults();
    GathererType GetResultsSoFar() const;
    bool Publish();
    inline unsigned long GetNumPlayerDone() const;

    StatsGathererEGT* clone() const;

  private:

    PairType sums; //first -- A; second -- B
    unsigned long stepDone;
    GathererType hisResults;

  }; //StatsGathererEGT

  unsigned long StatsGathererEGT::GetNumPlayerDone() const
  {
    return (sums.first+sums.second);
  }

}

#endif
