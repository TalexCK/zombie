#include "pvz/Zombies/BucketZombie.hpp"

BucketZombie::BucketZombie()
    : Zombie(ImageID::BUCKET_HEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::WALK, 1450)
{
  m_zombieType = ZombieType::BUCKET;
}

void BucketZombie::Update()
{
  if (!isLive())
    return;
  if (!m_eating)
    MoveTo(GetX() - 1, GetY());
  if (m_hp <= 200)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
void BucketZombie::OnClick() {}
