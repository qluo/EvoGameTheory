#ifndef PLAYER_FACTORY_INITIALIZER_H
#define PLAYER_FACTORY_INITIALIZER_H

#include "PlayerFactory.h"
#include "PlayerNormal.h"

namespace EGT
{
  class PlayerFactoryInitializer
  {
    static PlayerFactoryInitializer pfi;
    PlayerFactoryInitializer() {
      PlayerFactory::factory["Normal"] = new PlayerNormal::Factory;
    }
    ~PlayerFactoryInitializer() {
      std::map<std::string, PlayerFactory*>::iterator it = PlayerFactory::factory.begin();
      while(it != PlayerFactory::factory.end()) delete (it++)->second;
    }
  };

}

#endif
