#include "pvz/Plants/SunFlower.hpp"

#include "pvz/Plants/Plant.hpp"

SunFlower::SunFlower()
    : Plant(ImageID::SUNFLOWER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 340)
{
}

void SunFlower::Update()
{
  if (!isLive())
    return;
}
void SunFlower::OnClick() {}