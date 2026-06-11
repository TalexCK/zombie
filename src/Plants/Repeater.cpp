#include "pvz/Plants/Repeater.hpp"

#include "pvz/Plants/Plant.hpp"
#include "pvz/Projectiles/Pea.hpp"

Repeater::Repeater()
    : Plant(ImageID::REPEATER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
            60, 80, AnimID::IDLE, 340)
{
}

void Repeater::Update()
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
    if (ifSecond)
    {
      cooldown = 32;
    }
    else
    {
      cooldown = 4;
    }
    ifSecond = !ifSecond;
  }
  updateShooting(false);
}
void Repeater::OnClick() {}

void Repeater::updateShooting(bool shooting)
{
  ifShooting = shooting;
}