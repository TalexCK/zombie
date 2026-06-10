#include "pvz/Plants/Plant.hpp"

Plant::Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID)
{
  m_hp = hp;
}

void Plant::Update() {}
void Plant::OnClick() {}

void Plant::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + m_col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + m_row * LAWN_GRID_HEIGHT);
}

void Plant::decreaseHp(int damage)
{
  m_hp -= damage;
}

bool Plant::isLive()
{
  return m_hp > 0;
}

void Plant::setHp(int hp)
{
  this->m_hp = hp;
}