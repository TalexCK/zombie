#include "pvz/Zombies/Zombie.hpp"
#include "pvz/Plants/Plant.hpp"

Zombie::Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
    : GameObject(imageID, x, y, layer, width, height, animID), m_hp(hp)
{
  setZombie();
}

void Zombie::Update()
{
  if (!isLive())
    return;
  moveZombie();
}

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
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT + ZOMBIE_HEIGHT_OFFSET);
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

bool Zombie::attackPlant(Plant &plant)
{
  plant.decreaseHp(ZOMBIE_ATTACK_DAMAGE);
  return true;
}

void Zombie::afterCollisionCheck()
{
}

void Zombie::moveZombie()
{
  if (!m_eating)
    MoveTo(GetX() - ZOMBIE_WALK_SPEED, GetY());
  const int zombieHalfWidth = GetWidth() / 2;
  if (GetX() + zombieHalfWidth < 0)
    if_live = false;
}

void Zombie::setZombieType(ZombieType zombieType)
{
  m_zombieType = zombieType;
}

bool Zombie::canBeTargetedByShooter() const
{
  return true;
}

ZombieType Zombie::getZombieType() const
{
  return m_zombieType;
}
