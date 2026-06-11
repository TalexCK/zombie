#include "pvz/Plants/Shooter.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

Shooter::Shooter(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp)
    : Plant(imageID, x, y, layer, width, height, animID, hp)
{
}

void Shooter::Update()
{
  if (!isLive())
    return;
  if (cooldown > 0)
  {
    cooldown--;
  }
  else
  {
    if (ifShooting)
    {
      if (auto world = m_world.lock())
      {
        world->generatePea(m_row, m_col);
      }
    }
    cooldown = getNextCooldown();
  }
  updateShooting(false);
}

bool Shooter::canShoot() const
{
  return true;
}

void Shooter::updateShooting(bool shooting)
{
  ifShooting = shooting;
}

int Shooter::getNextCooldown()
{
  return SHOOTER_COOLDOWN_TICKS;
}
