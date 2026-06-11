#ifndef CONEHEADZOMBIE_HPP
#define CONEHEADZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class ConeheadZombie : public Zombie
{
public:
  ConeheadZombie();

  void Update() override;
};

#endif // !CONEHEADZOMBIE_HPP
