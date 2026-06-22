#include "pvz/Zombies/PoleZombie.hpp"
#include "pvz/Plants/Plant.hpp"

PoleZombie::PoleZombie()
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::RUN, POLE_ZOMBIE_HP)
{
  setZombieType(ZombieType::POLE);
}

void PoleZombie::Update()
{
  if (!isLive())
    return;
  if (frame_count > 0 && !m_running)
  {
    frame_count--;
  }
  else if (frame_count == 0 && !m_running)
  {
    PlayAnimation(AnimID::WALK);
    MoveTo(GetX() - POLE_JUMP_FORWARD_DISTANCE, GetY());
    if (GetX() < ZOMBIE_LEFT_BOUNDARY_X)
      MoveTo(ZOMBIE_LEFT_BOUNDARY_X, GetY());
    frame_count = -1;
  }
  else
  {
    if (!m_eating)
    {
      if (m_running)
      {
        MoveTo(GetX() - ZOMBIE_WALK_SPEED, GetY());
      }
      MoveTo(GetX() - ZOMBIE_WALK_SPEED, GetY());
    }
    if (m_running)
    {
      MoveTo(GetX() - POLE_JUMP_COLLISION_OFFSET, GetY());
    }
  }
  const int realX = ifRunning() ? GetX() + POLE_JUMP_COLLISION_OFFSET : GetX();
  const int zombieHalfWidth = GetWidth() / 2;
  if (realX + zombieHalfWidth < 0)
  {
    if_live = false;
  }
}

bool PoleZombie::ifRunning() const
{
  return m_running;
}

void PoleZombie::shouldJump()
{
  m_running = false;
  frame_count = POLE_JUMP_FRAME_COUNT;
  PlayAnimation(AnimID::JUMP);
}

bool PoleZombie::ifJumpping() const
{
  return frame_count >= 0 && !m_running;
}

bool PoleZombie::attackPlant(Plant &plant)
{
  if (!ifRunning() && !ifJumpping())
  {
    plant.decreaseHp(ZOMBIE_ATTACK_DAMAGE);
    return true;
  }
  else if (!ifJumpping())
  {
    MoveTo(GetX() + POLE_JUMP_COLLISION_OFFSET, GetY());
    shouldJump();
  }
  return false;
}

void PoleZombie::afterCollisionCheck()
{
  if (ifRunning())
  {
    MoveTo(GetX() + POLE_JUMP_COLLISION_OFFSET, GetY());
  }
}

bool PoleZombie::canBeTargetedByShooter() const
{
  return !ifJumpping();
}
