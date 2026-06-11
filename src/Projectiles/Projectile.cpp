#include "pvz/Projectiles/Projectile.hpp"

Projectile::Projectile(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID)
{
  setProjectile();
}

void Projectile::Update() {}
void Projectile::OnClick() {}

bool Projectile::isActive() const
{
  return false;
}

int Projectile::getDamage() const
{
  return 0;
}

void Projectile::deactive()
{
}

void Projectile::kill()
{
  if_live = false;
}
