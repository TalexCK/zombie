#include "pvz/Plants/WallNut.hpp"

#include "pvz/Plants/Plant.hpp"

WallNut::WallNut()
    : Plant(ImageID::WALLNUT, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            PLANT_WIDTH, PLANT_HEIGHT, AnimID::IDLE, WALLNUT_HP)
{
}

void WallNut::Update()
{
  if (!isLive())
    return;
  if (m_hp <= WALLNUT_CRACKED_HP)
  {
    ChangeImage(ImageID::WALLNUT_CRACKED);
  }
}
