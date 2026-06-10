#include "pvz/Plants/SunFlower.hpp"

#include "pvz/Plants/Plant.hpp"

SunFlower::SunFlower()
    : Plant(ImageID::SUNFLOWER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            0, 0, AnimID::IDLE, 100)
{
}

void SunFlower::Update() {}
void SunFlower::OnClick() {}