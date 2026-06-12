#include "pvz/Zombies/ConeheadZombie.hpp"

ConeheadZombie::ConeheadZombie()
    : Zombie(ImageID::CONEHEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::WALK, CONEHEAD_ZOMBIE_HP)
{
  setZombieType(ZombieType::CONEHEAD);
}

void ConeheadZombie::Update()
{
  Zombie::Update();
  if (!isLive())
    return;
  if (m_hp <= HEADGEAR_LOST_HP_THRESHOLD)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
