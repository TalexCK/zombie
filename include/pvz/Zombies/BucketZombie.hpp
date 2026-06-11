#ifndef BUCKETZOMBIE_HPP
#define BUCKETZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class BucketZombie : public Zombie
{
public:
  BucketZombie();

  void Update() override;
};

#endif // !BUCKETZOMBIE_HPP
