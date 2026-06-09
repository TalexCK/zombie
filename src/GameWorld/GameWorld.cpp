#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/Objects/Background.hpp"

void GameWorld::Init()
{
  m_objects.clear();
  m_objects.push_back(std::make_shared<Background>());
}

LevelStatus GameWorld::Update()
{
  // YOUR CODE HERE
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
}
