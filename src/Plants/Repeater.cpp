#include "pvz/Plants/Repeater.hpp"

#include "pvz/Plants/Plant.hpp"

Repeater::Repeater()
    : Plant(ImageID::REPEATER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            0, 0, AnimID::IDLE, 100)
{
}

void Repeater::Update() {}
void Repeater::OnClick() {}
