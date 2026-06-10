#include "pvz/Zombies/Zombie.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID)
{
  m_hp = hp;
}

void Zombie::Update() {}
void Zombie::OnClick() {}

void Zombie::setLocation(int col, int row)
{
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT);
}