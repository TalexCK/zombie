#include "pvz/Plants/SunFlower.hpp"

#include "pvz/Plants/Plant.hpp"

SunFlower::SunFlower()
    : Plant(ImageID::SUNFLOWER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            PLANT_WIDTH, PLANT_HEIGHT, AnimID::IDLE, BASIC_PLANT_HP)
{
}

void SunFlower::Update()
{
  if (!isLive())
    return;
}

bool SunFlower::shouldDropSun() const
{
  return true;
}
