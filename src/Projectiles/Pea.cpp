#include "pvz/Projectiles/Pea.hpp"

Pea::Pea()
    : Projectile(ImageID::PEA, 0, 0, LayerID::PROJECTILES, 28, 28, AnimID::NO_ANIMATION), active(true)
{
}

void Pea::Update()
{
  if (!isLive())
    return;
  MoveTo(GetX() + 8, GetY());
  if (GetX() > WINDOW_WIDTH)
  {
    kill();
  }
}

void Pea::setPosition(int row, int col)
{
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH + 30, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT + 12);
}

void Pea::deactive()
{
  active = false;
}

bool Pea::isActive() const
{
  return active;
}

int Pea::getDamage() const
{
  return 24;
}
