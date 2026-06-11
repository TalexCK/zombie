#include "pvz/Zombies/ConeheadZombie.hpp"

ConeheadZombie::ConeheadZombie()
    : Zombie(ImageID::CONEHEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::WALK, 560)
{
  m_zombieType = ZombieType::CONEHEAD;
}

void ConeheadZombie::Update()
{
  if (!isLive())
    return;
  if (!m_eating)
    MoveTo(GetX() - 1, GetY());
  if (m_hp <= 200)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
void ConeheadZombie::OnClick() {}
