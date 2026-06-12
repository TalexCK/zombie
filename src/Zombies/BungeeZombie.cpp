#include "pvz/Zombies/BungeeZombie.hpp"
#include "pvz/Plants/Plant.hpp"

BungeeZombie::BungeeZombie()
    : Zombie(ImageID::BUNGEE_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::NO_ANIMATION, BUNGEE_ZOMBIE_HP)
{
  setZombieType(ZombieType::BUNGEE);
}

void BungeeZombie::Update()
{
  if (!isLive())
    return;
  if (frame_count == 0)
  {
    frame_count = -1;
  }
  if (getStage() == BUNGEE_DESCENDING_STAGE)
  {
    MoveTo(GetX(), GetY() - BUNGEE_VERTICAL_SPEED);
  }
  else if (getStage() == BUNGEE_GRABBING_STAGE)
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
    MoveTo(GetX(), GetY() + BUNGEE_VERTICAL_SPEED);
  }
  if (GetY() <= goalY && stage == BUNGEE_DESCENDING_STAGE)
  {
    ChangeImage(ImageID::BUNGEE_ZOMBIE_GRAB);
    nextStage();
  }
  if (GetY() >= goalYup && stage == BUNGEE_ASCENDING_STAGE)
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
  goalYup = FIRST_ROW_CENTER + (BUNGEE_TOP_ROW_SCALE * row + BUNGEE_TOP_ROW_OFFSET) * LAWN_GRID_HEIGHT / BUNGEE_TOP_ROW_DIVISOR;
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH,
         FIRST_ROW_CENTER + (BUNGEE_TOP_ROW_SCALE * row + BUNGEE_TOP_ROW_OFFSET) * LAWN_GRID_HEIGHT / BUNGEE_TOP_ROW_DIVISOR);
}

int BungeeZombie::getFrameCount() const
{
  return frame_count;
}

bool BungeeZombie::attackPlant(Plant &plant)
{
  if (getStage() == BUNGEE_ASCENDING_STAGE && getFrameCount() == 0)
  {
    plant.decreaseHp(INSTANT_KILL_DAMAGE);
  }
  return false;
}
