#include "pvz/Plants/Repeater.hpp"

Repeater::Repeater()
    : Shooter(ImageID::REPEATER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
              PLANT_WIDTH, PLANT_HEIGHT, AnimID::IDLE, BASIC_PLANT_HP)
{
}

int Repeater::getNextCooldown()
{
  int nextCooldown = REPEATER_SECOND_SHOT_COOLDOWN_TICKS;
  if (ifSecond)
  {
    nextCooldown = SHOOTER_COOLDOWN_TICKS;
  }
  ifSecond = !ifSecond;
  return nextCooldown;
}
