#include "pvz/Plants/PeaShooter.hpp"

#include "pvz/Plants/Plant.hpp"

PeaShooter::PeaShooter()
    : Plant(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            0, 0, AnimID::IDLE, 100)
{
}

void PeaShooter::Update() {}
void PeaShooter::OnClick() {}
