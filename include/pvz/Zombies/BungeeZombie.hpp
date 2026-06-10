#ifndef BUNGEEZOMBIE_HPP
#define BUNGEEZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class BungeeZombie : public Zombie
{
public:
  BungeeZombie();

  void Update() override;
  void OnClick() override;
};

#endif // !BUNGEEZOMBIE_HPP
