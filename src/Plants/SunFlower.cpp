#include "pvz/Plants/SunFlower.hpp"

SunFlower::SunFlower()
    : GameObject(ImageID::SUNFLOWER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
                 0, 0, AnimID::IDLE)
{
}

void SunFlower::Update() {}
void SunFlower::OnClick() {}

void SunFlower::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + m_col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + m_row * LAWN_GRID_HEIGHT);
}