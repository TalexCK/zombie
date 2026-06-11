#include "pvz/Objects/ZombiePlace.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

ZombiePlace::ZombiePlace()
    : GameObject(ImageID::NONE, 0, 0, LayerID::UI,
                 LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT - 10, AnimID::NO_ANIMATION)
{
}

void ZombiePlace::Update() {}
void ZombiePlace::OnClick()
{
  bool isCrash = false;
  for (auto &obj : m_world->getObjects())
  {
    if (ifCrashObject(*obj) && obj->ifZombie())
    {
      isCrash = true;
      break;
    }
  }
  if (m_world->isZombieChoosed() && !isCrash)
  {
    if (m_world->placeZombie(m_row, m_col))
    {
      m_world->cancelZombieChoosed();
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
