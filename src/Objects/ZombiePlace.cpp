#include "pvz/Objects/ZombiePlace.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

ZombiePlace::ZombiePlace()
    : GameObject(ImageID::NONE, 0, 0, LayerID::RABBIT,
                 LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT - 10, AnimID::NO_ANIMATION)
{
}

void ZombiePlace::Update() {}
void ZombiePlace::OnClick()
{
  auto world = m_world.lock();
  if (!world)
    return;
  bool isCrash = false;
  for (auto &obj : world->getObjects())
  {
    if (ifCrashObject(*obj) && obj->ifZombie())
    {
      isCrash = true;
      break;
    }
  }
  if (world->isZombieChoosed() && !isCrash)
  {
    if (world->placeZombie(m_row, m_col))
    {
      world->cancelZombieChoosed();
    }
  }
}

void ZombiePlace::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT);
}

void ZombiePlace::setGameWorld(std::shared_ptr<GameWorld> world)
{
  m_world = world;
}
