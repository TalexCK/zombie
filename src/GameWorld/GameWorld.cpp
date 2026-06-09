#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/Objects/Background.hpp"
#include "pvz/Objects/ProgressBar.hpp"
#include "pvz/Objects/Brain.hpp"
#include "pvz/Objects/RedLine.hpp"
#include "pvz/Objects/ZombieCard.hpp"
#include "pvz/Objects/ZombiePlace.hpp"

void GameWorld::Init()
{
  m_objects.clear();
  m_objects.push_back(std::make_shared<Background>());

  addSun(150);
  initBrains();
  initZombieCards();
  initZombiePlaces();
  m_sunText = std::make_shared<TextBase>(SUN_COUNTER_X, SUN_COUNTER_Y);
  m_sunText->SetText(std::to_string(getSunCount()));
  m_sunText->SetColor(0, 0, 0);

  m_infoText = std::make_shared<TextBase>(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 40);
  m_infoText->SetText("Stage " + std::to_string(m_stage) + "/" + std::to_string(TOTAL_ROUNDS) + "  Brains: " + std::to_string(m_brains));
  m_infoText->SetColor(255, 255, 255);

  m_progressBar = std::make_shared<ProgressBar>();
  m_objects.push_back(m_progressBar);
  m_progressBar->setStage(m_stage);

  m_deploymentStartCol = ZOMBIE_DEPLOYMENT_BUFFER_COLS;

  m_redLine = std::make_shared<RedLine>();
  m_objects.push_back(m_redLine);
  m_redLine->updateColLeft(m_deploymentStartCol);

  updateStage();
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

int GameWorld::getSunCount() const { return m_sunCount; }
void GameWorld::addSun(int count)
{
  m_sunCount += count;
}
bool GameWorld::consumeSun(int count)
{
  if (m_sunCount < count)
    return false;
  m_sunCount -= count;
  return true;
}

bool GameWorld::decreaseBrains()
{
  m_brains--;
  if (m_brains <= 0)
    return true;
  return false;
}

bool GameWorld::updateStage()
{
  m_stage++;
  m_deploymentStartCol++;
  m_redLine->updateColLeft(m_deploymentStartCol);
  if (m_stage > TOTAL_ROUNDS)
    return false;
  return true;
}

void GameWorld::initBrains()
{
  m_brains = 5;
  for (int i = 0; i < m_brains; i++)
  {
    std::shared_ptr<Brain> brain = std::make_shared<Brain>();
    brain->setID(i);
    m_objects.push_back(brain);
  }
}

void GameWorld::initZombieCards()
{
  for (int i = 0; i < 5; i++)
  {
    std::shared_ptr<ZombieCard> zombieCard = std::make_shared<ZombieCard>();
    zombieCard->setType(static_cast<ZombieType>(i));
    m_objects.push_back(zombieCard);
  }
}

void GameWorld::initZombiePlaces()
{
  for (int i = 0; i < GAME_ROWS * (GAME_COLS - m_deploymentStartCol); i++)
  {
    std::shared_ptr<ZombiePlace> zombiePlace = std::make_shared<ZombiePlace>();
    m_objects.push_back(zombiePlace);
    zombiePlace->setPosition(i % GAME_ROWS, i / GAME_ROWS + m_deploymentStartCol);
  }
}

bool GameWorld::setAsPlantAt(int x, int y)
{
  if (ifPlantAt(x, y))
    return false;
  m_blocks[y * GAME_COLS + x] = 1;
  return true;
}

bool GameWorld::removeAsPlantAt(int x, int y)
{
  if (!ifPlantAt(x, y))
    return false;
  m_blocks[y * GAME_COLS + x] = 0;
  return true;
}

bool GameWorld::ifPlantAt(int x, int y) const
{
  if (!(x >= 0 && x < GAME_COLS && y >= 0 && y < GAME_ROWS))
    return false;
  return m_blocks[y * GAME_COLS + x] == 1;
}