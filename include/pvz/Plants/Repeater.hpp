#ifndef REPEATER_HPP
#define REPEATER_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Shooter.hpp"

class Repeater : public Shooter
{
public:
  Repeater();

private:
  int getNextCooldown() override;

  bool ifSecond = false;
};

#endif // !REPEATER_HPP