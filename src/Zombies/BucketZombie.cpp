#include "pvz/Zombies/BucketZombie.hpp"

BucketZombie::BucketZombie()
    : Zombie(ImageID::BUCKET_HEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::WALK, BUCKET_ZOMBIE_HP)
{
  setZombieType(ZombieType::BUCKET);
}

void BucketZombie::Update()
{
  Zombie::Update();
  if (!isLive())
    return;
  if (m_hp <= HEADGEAR_LOST_HP_THRESHOLD)
    ChangeImage(ImageID::REGULAR_ZOMBIE);
}
