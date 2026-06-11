#include "pvz/Plants/PeaShooter.hpp"

#include "pvz/Plants/Plant.hpp"
#include "pvz/Projectiles/Pea.hpp"

PeaShooter::PeaShooter()
    : Plant(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 340)
{
  cooldown = 32;
}

void PeaShooter::Update()
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
      m_world->generatePea(m_row, m_col);
    cooldown = 32;
  }
  updateShooting(false);
}
void PeaShooter::OnClick() {}

void PeaShooter::updateShooting(bool shooting)
{
  ifShooting = shooting;
}