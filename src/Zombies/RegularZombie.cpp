#include "pvz/Zombies/RegularZombie.hpp"

RegularZombie::RegularZombie()
    : Zombie(ImageID::REGULAR_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::WALK, 260)
{
  m_zombieType = ZombieType::REGULAR;
}

void RegularZombie::Update()
{
  if (!isLive())
    return;
  if (!m_eating)
    MoveTo(GetX() - 1, GetY());
}
void RegularZombie::OnClick() {}