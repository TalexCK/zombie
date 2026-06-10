#ifndef REGULARZOMBIE_HPP
#define REGULARZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class RegularZombie : public Zombie
{
public:
  RegularZombie();

  void Update() override;
  void OnClick() override;
};

#endif // !REGULARZOMBIE_HPP