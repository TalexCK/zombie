#include "pvz/Plants/PeaShooter.hpp"

PeaShooter::PeaShooter()
    : GameObject(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
                 0, 0, AnimID::IDLE)
{
}

void PeaShooter::Update() {}
void PeaShooter::OnClick() {}

void PeaShooter::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + m_col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + m_row * LAWN_GRID_HEIGHT);
}

void PeaShooter::decreaseHP(int damage)
{
  hp -= damage;
}

bool PeaShooter::isLive()
{
  return hp > 0;
}