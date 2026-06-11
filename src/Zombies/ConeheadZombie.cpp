#include "pvz/Zombies/ConeheadZombie.hpp"

ConeheadZombie::ConeheadZombie()
    : Zombie(ImageID::CONEHEAD_ZOMBIE, WINDOW_WIDTH / WINDOW_CENTER_DIVISOR, WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::WALK, CONEHEAD_ZOMBIE_HP)
{
}

void ConeheadZombie::Update()
{
  Zombie::Update();
  if (!isLive())
    return;
  if (m_hp <= HEADGEAR_LOST_HP_THRESHOLD)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
