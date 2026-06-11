#include "pvz/Plants/Repeater.hpp"

Repeater::Repeater()
    : Shooter(ImageID::REPEATER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
              60, 80, AnimID::IDLE, 340)
{
}

int Repeater::getNextCooldown()
{
  int nextCooldown = 4;
  if (ifSecond)
  {
    nextCooldown = 32;
  }
  ifSecond = !ifSecond;
  return nextCooldown;
}
