#include "pvz/Zombies/BungeeZombie.hpp"
#include "pvz/Plants/Plant.hpp"

BungeeZombie::BungeeZombie()
    : Zombie(ImageID::BUNGEE_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::NO_ANIMATION, 450)
{
}

void BungeeZombie::Update()
{
  if (!isLive())
    return;
  if (frame_count == 0)
  {
    frame_count = -1;
  }
  if (getStage() == 0)
  {
    MoveTo(GetX(), GetY() - 6);
  }
  else if (getStage() == 1)
  {
    frame_count--;
    if (frame_count == 0)
    {
      ChangeImage(ImageID::BUNGEE_ZOMBIE);
      nextStage();
    }
  }
  else
  {
    MoveTo(GetX(), GetY() + 6);
  }
  if (GetY() <= goalY && stage == 0)
  {
    ChangeImage(ImageID::BUNGEE_ZOMBIE_GRAB);
    nextStage();
  }
  if (GetY() >= goalYup && stage == 2)
  {
    if_live = false;
  }
}

int BungeeZombie::getStage() const
{
  return stage;
}

void BungeeZombie::nextStage()
{
  stage++;
}

void BungeeZombie::setBungeeLocation(int col, int row)
{
  goalY = FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT;
  goalYup = FIRST_ROW_CENTER + (2 * row + 3) * LAWN_GRID_HEIGHT / 2;
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + (2 * row + 3) * LAWN_GRID_HEIGHT / 2);
}

int BungeeZombie::getFrameCount() const
{
  return frame_count;
}

bool BungeeZombie::attackPlant(Plant &plant)
{
  if (getStage() == 2 && getFrameCount() == 0)
  {
    plant.decreaseHp(100000);
  }
  return false;
}
