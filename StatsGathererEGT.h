#ifndef STATS_GATHERER_EGT_H
#define STATS_GATHERER_EGT_H

namespace EGT {

  class StatsGathererEGT :
  {
  public:
    StatsGathererEGT();
    void DumpOneResult(unsigned result);
    std::vector< std::vector<unsigned> > GetResultsSoFar() const;
    bool Publish() const;
    StatsGathererEGT* clone() const;

  private:
    unsigned sumOfOne;
    unsigned long PlayerDone;

  }; //StatsGathererEGT

}
#endif
