#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include <map>
#include <string>
#include "PlayerBase.h"

namespace EGT{

class PlayerFactory 
{
 public:
  virtual ~PlayerFactory() {}
  friend class PlayerFactoryInitializer;
  static PlayerBase* createPlayer(const std::string& id, const unsigned& numStrat, const unsigned long& memSize);
 private:
  static std::map<std::string, PlayerFactory*> factory;
  virtual PlayerBase* create(const unsigned& numStrat, const unsigned long& memSize) = 0;
};

} // namespace EGT

#endif
