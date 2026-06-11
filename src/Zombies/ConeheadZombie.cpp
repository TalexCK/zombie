#include "pvz/Zombies/ConeheadZombie.hpp"

ConeheadZombie::ConeheadZombie()
    : Zombie(ImageID::CONEHEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::WALK, 560)
{
}

void ConeheadZombie::Update()
{
  Zombie::Update();
  if (!isLive())
    return;
  if (m_hp <= 200)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
