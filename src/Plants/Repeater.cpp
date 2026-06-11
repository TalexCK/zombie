#include "pvz/Plants/Repeater.hpp"

#include "pvz/Plants/Plant.hpp"

Repeater::Repeater()
    : Plant(ImageID::REPEATER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 340)
{
}

void Repeater::Update()
{
  if (!isLive())
    return;
}
void Repeater::OnClick() {}
