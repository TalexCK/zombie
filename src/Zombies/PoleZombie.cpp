#include "pvz/Zombies/PoleZombie.hpp"
#include "pvz/Plants/Plant.hpp"

PoleZombie::PoleZombie()
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, WINDOW_WIDTH / WINDOW_CENTER_DIVISOR, WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::RUN, POLE_ZOMBIE_HP)
{
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
  if (GetX() < ZOMBIE_LEFT_BOUNDARY_X)
  {
    ChangeImage(ImageID::NONE);
    MoveTo(ZOMBIE_LEFT_BOUNDARY_X, GetY());
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
