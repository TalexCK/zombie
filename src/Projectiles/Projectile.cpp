#include "pvz/Projectiles/Projectile.hpp"

Projectile::Projectile(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : GameObject(imageID, x, y, layer, width, height, animID)
{
}

void Projectile::Update() {}
void Projectile::OnClick() {}

void Projectile::kill()
{
  if_live = false;
}