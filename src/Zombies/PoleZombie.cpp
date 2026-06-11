#include "pvz/Zombies/PoleZombie.hpp"
#include "pvz/Plants/Plant.hpp"

PoleZombie::PoleZombie()
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::RUN, 420)
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
    MoveTo(GetX() - 150, GetY());
    frame_count = -1;
  }
  else
  {
    if (!m_eating)
    {
      if (m_running)
      {
        MoveTo(GetX() - 1, GetY());
      }
      MoveTo(GetX() - 1, GetY());
    }
    if (m_running)
    {
      MoveTo(GetX() - 40, GetY());
    }
  }
  if (GetX() < 35)
  {
    ChangeImage(ImageID::NONE);
    MoveTo(35, GetY());
  }
}

bool PoleZombie::ifRunning() const
{
  return m_running;
}

void PoleZombie::shouldJump()
{
  m_running = false;
  frame_count = 41;
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
    plant.decreaseHp(4);
    return true;
  }
  else if (!ifJumpping())
  {
    MoveTo(GetX() + 40, GetY());
    shouldJump();
  }
  return false;
}

void PoleZombie::afterCollisionCheck()
{
  if (ifRunning())
  {
    MoveTo(GetX() + 40, GetY());
  }
}
