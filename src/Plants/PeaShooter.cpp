#include "pvz/Plants/PeaShooter.hpp"

#include "pvz/Plants/Plant.hpp"

PeaShooter::PeaShooter()
    : Plant(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 340)
{
}

void PeaShooter::Update()
{
  if (!isLive())
    return;
}
void PeaShooter::OnClick() {}
