#include "pvz/Zombies/Zombie.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID)
{
  m_hp = hp;
  setZombie();
}

void Zombie::Update() {}
void Zombie::OnClick() {}

bool Zombie::isEating() const
{
  return m_eating;
}

void Zombie::setEating(bool eating)
{
  m_eating = eating;
  if (m_eating)
  {
    m_currentAnim = GetCurrentAnimation();
    PlayAnimation(AnimID::EAT);
  }
  else
  {
    PlayAnimation(m_currentAnim);
  }
}

void Zombie::setLocation(int col, int row)
{
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT);
}

void Zombie::decreaseHp(int hp)
{
  m_hp -= hp;
  if (m_hp <= 0)
  {
    m_hp = 0;
    if_live = false;
  }
}

ZombieType Zombie::getZombieType() const
{
  return m_zombieType;
}