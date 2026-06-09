#include "pvz/Plants/WallNut.hpp"

WallNut::WallNut()
    : GameObject(ImageID::WALLNUT, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
                 0, 0, AnimID::IDLE)
{
}

void WallNut::Update() {}
void WallNut::OnClick() {}

void WallNut::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + m_col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + m_row * LAWN_GRID_HEIGHT);
}

void WallNut::decreaseHP(int damage)
{
  hp -= damage;
}

bool WallNut::isLive()
{
  return hp > 0;
}