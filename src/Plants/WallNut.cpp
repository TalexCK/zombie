#include "pvz/Plants/WallNut.hpp"

#include "pvz/Plants/Plant.hpp"

WallNut::WallNut()
    : Plant(ImageID::WALLNUT, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            0, 0, AnimID::IDLE, 100)
{
}

void WallNut::Update() {}
void WallNut::OnClick() {}
