#include "pvz/Plants/WallNut.hpp"

#include "pvz/Plants/Plant.hpp"

WallNut::WallNut()
    : Plant(ImageID::WALLNUT, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 3600)
{
}

void WallNut::Update()
{
  if (!isLive())
    return;
  if (m_hp <= 1800)
  {
    ChangeImage(ImageID::WALLNUT_CRACKED);
  }
}
void WallNut::OnClick() {}
