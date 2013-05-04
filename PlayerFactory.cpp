#include "PlayerFactory.h"
#include "MyUtils.h"

EGT::PlayerBase* EGT::PlayerFactory::createPlayer(const std::string& id, const unsigned& numStrat, const unsigned long& memSize)
{
  myUtils::check(factory.find(id) != factory.end(), "ERROR: PlayerFactory::createPlayer(): Bad Player Creation");
  return factory[id]->create(numStrat, memSize);
}
