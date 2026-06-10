#ifndef POLEZOMBIE_HPP
#define POLEZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class PoleZombie : public Zombie
{
public:
  PoleZombie();

  void Update() override;
  void OnClick() override;
};

#endif // !POLEZOMBIE_HPP
