#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/Objects/Background.hpp"
#include "pvz/Objects/ProgressBar.hpp"
#include "pvz/Objects/Brain.hpp"
#include "pvz/Objects/RedLine.hpp"
#include "pvz/Objects/ZombieCard.hpp"
#include "pvz/Objects/ZombiePlace.hpp"
#include "pvz/Objects/CardHover.hpp"
#include "pvz/Plants/SunFlower.hpp"
#include "pvz/Plants/PeaShooter.hpp"
#include "pvz/Plants/Repeater.hpp"
#include "pvz/Plants/WallNut.hpp"
#include "pvz/Zombies/RegularZombie.hpp"
#include "pvz/Zombies/ConeheadZombie.hpp"
#include "pvz/Zombies/PoleZombie.hpp"
#include "pvz/Zombies/BucketZombie.hpp"
#include "pvz/Zombies/BungeeZombie.hpp"
#include "pvz/Objects/Sun.hpp"

void GameWorld::Init()
{

  m_zombieChoosed = false;
  m_objects.clear();
  m_objects.push_back(std::make_shared<Background>());

  m_stageEnded = false;

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

  m_deploymentStartCol = ZOMBIE_DEPLOYMENT_BUFFER_COLS;

  m_redLine = std::make_shared<RedLine>();
  m_objects.push_back(m_redLine);
  m_redLine->updateColLeft(m_deploymentStartCol);

  updateStage();
  m_progressBar->setStage(m_stage);
  generatePlant(m_deploymentStartCol - 1);
}

LevelStatus GameWorld::Update()
{
  for (auto &obj : m_objects)
  {
    obj->Update();
  }
  for (auto &obj : m_waitingObjects)
  {
    m_objects.push_back(obj);
  }
  m_waitingObjects.clear();
  m_sunText->SetText(std::to_string(getSunCount()));
  m_infoText->SetText("Stage " + std::to_string(m_stage) + "/" + std::to_string(TOTAL_ROUNDS) + "  Brains: " + std::to_string(m_brains));

  for (auto &obj : m_objects)
  {
    if (obj->ifZombie())
    {
      bool eating = false;
      std::shared_ptr<Zombie> zombie = std::dynamic_pointer_cast<Zombie>(obj);
      for (auto &other : m_objects)
      {
        if (obj != other && obj->ifCrashObject(*other))
        {
          if (other->ifPlant())
          {
            if (zombie->getZombieType() != ZombieType::POLE && zombie->getZombieType() != ZombieType::BUNGEE)
            {
              eating = true;
              std::shared_ptr<Plant> plant = std::dynamic_pointer_cast<Plant>(other);
              plant->decreaseHp(4);
              continue;
            }
            else if (zombie->getZombieType() == ZombieType::POLE)
            {
              std::shared_ptr<PoleZombie> poleZombie = std::dynamic_pointer_cast<PoleZombie>(obj);
              if (!poleZombie->ifRunning() && !poleZombie->ifJumpping())
              {
                eating = true;
                std::shared_ptr<Plant> plant = std::dynamic_pointer_cast<Plant>(other);
                plant->decreaseHp(4);
                continue;
              }
              else if (!poleZombie->ifJumpping())
              {
                poleZombie->MoveTo(poleZombie->GetX() + 40, poleZombie->GetY());
                poleZombie->shouldJump();
              }
            }
            else if (zombie->getZombieType() == ZombieType::BUNGEE)
            {
              std::shared_ptr<BungeeZombie> bungeeZombie = std::dynamic_pointer_cast<BungeeZombie>(obj);
              if (bungeeZombie->getStage() == 2 && bungeeZombie->getFrameCount() == 0)
              {
                std::shared_ptr<Plant> plant = std::dynamic_pointer_cast<Plant>(other);
                plant->decreaseHp(100000);
                continue;
              }
            }
          }
          if (std::shared_ptr<Brain> brain = std::dynamic_pointer_cast<Brain>(other))
          {
            brain->die();
            zombie->decreaseHp(100000);
            if (decreaseBrains())
            {
              m_stageEnded = true;
            }
            continue;
          }
        }
      }
      if (std::shared_ptr<PoleZombie> poleZombie = std::dynamic_pointer_cast<PoleZombie>(obj))
      {
        if (poleZombie->ifRunning())
        {
          poleZombie->MoveTo(poleZombie->GetX() + 40, poleZombie->GetY());
        }
      }
      if (!zombie->isEating() && eating)
        zombie->setEating(eating);
      if (zombie->isEating() && !eating)
        zombie->setEating(eating);
    }
  }

  for (auto &obj : m_objects)
  {
    if (std::shared_ptr<Brain> brain = std::dynamic_pointer_cast<Brain>(obj))
    {
      if (!brain->isLive())
        obj.reset();
      continue;
    }
    if (obj->ifPlant())
    {
      if (!obj->isLive())
      {
        if (std::shared_ptr<SunFlower> sunflower = std::dynamic_pointer_cast<SunFlower>(obj))
        {
          for (int i = 0; i < 6; i++)
          {
            std::shared_ptr<Sun> sun = std::make_shared<Sun>();
            sun->setPosition(sunflower->GetX(), sunflower->GetY());
            m_waitingObjects.push_back(sun);
          }
        }
        const int col = (obj->GetX() - FIRST_COL_CENTER) / LAWN_GRID_WIDTH;
        const int row = (obj->GetY() - FIRST_ROW_CENTER) / LAWN_GRID_HEIGHT;
        removeAsPlantAt(col, row);
        obj.reset();
      }
      continue;
    }
    if (obj->ifSun())
    {
      if (!obj->isLive())
      {
        obj.reset();
        addSun(SUN_VALUE);
      }
      continue;
    }
    if (obj->ifZombie())
    {
      if (!obj->isLive())
      {
        obj.reset();
      }
      continue;
    }
    if (std::shared_ptr<CardHover> hover = std::dynamic_pointer_cast<CardHover>(obj))
    {
      if (!hover->isLive())
      {
        obj.reset();
      }
      continue;
    }
  }
  m_objects.remove_if([](const std::shared_ptr<GameObject> &obj)
                      { return obj == nullptr; });
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  m_objects.clear();
  m_sunText.reset();
  m_infoText.reset();
  m_progressBar.reset();
  m_redLine.reset();
  m_sunCount = 0;
  m_stage = 0;
  m_brains = 0;
  m_deploymentStartCol = INITIAL_ZOMBIE_DEPLOYMENT_START_COL + ZOMBIE_DEPLOYMENT_BUFFER_COLS;
  for (int i = 0; i < GAME_ROWS * GAME_COLS; ++i)
  {
    m_blocks[i] = 0;
  }
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
  for (ZombieType type : {ZombieType::REGULAR, ZombieType::CONEHEAD, ZombieType::POLE, ZombieType::BUCKET, ZombieType::BUNGEE})
  {
    std::shared_ptr<ZombieCard> zombieCard = std::make_shared<ZombieCard>();
    zombieCard->setType(type);
    zombieCard->setGameWorld(shared_from_this());
    m_objects.push_back(zombieCard);
  }
}

void GameWorld::initZombiePlaces()
{
  for (int i = 0; i < GAME_ROWS * GAME_COLS; i++)
  {
    std::shared_ptr<ZombiePlace> zombiePlace = std::make_shared<ZombiePlace>();
    m_objects.push_back(zombiePlace);
    zombiePlace->setGameWorld(shared_from_this());
    zombiePlace->setPosition(i % GAME_ROWS, i / GAME_ROWS);
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

void GameWorld::generatePlant(int cols)
{
  for (int col = 0; col < cols && col < GAME_COLS; col++)
  {
    for (int row = 0; row < GAME_ROWS; row++)
    {
      if (!ifPlantAt(col, row))
      {
        int plantType = randInt(0, 9);
        if (plantType <= 3)
        {
          std::shared_ptr<SunFlower> plant = std::make_shared<SunFlower>();
          plant->setPosition(row, col);
          m_waitingObjects.push_back(plant);
          setAsPlantAt(col, row);
        }
        else if (plantType <= 6)
        {
          std::shared_ptr<PeaShooter> plant = std::make_shared<PeaShooter>();
          plant->setPosition(row, col);
          m_waitingObjects.push_back(plant);
          setAsPlantAt(col, row);
        }
        else if (plantType <= 7)
        {
          std::shared_ptr<Repeater> plant = std::make_shared<Repeater>();
          plant->setPosition(row, col);
          m_waitingObjects.push_back(plant);
          setAsPlantAt(col, row);
        }
        else
        {
          std::shared_ptr<WallNut> plant = std::make_shared<WallNut>();
          plant->setPosition(row, col);
          m_waitingObjects.push_back(plant);
          setAsPlantAt(col, row);
        }
      }
    }
  }
}

void GameWorld::setZombieChoosed(ZombieType type)
{
  m_zombieChoosed = true;
  m_choosedZombieType = type;
}

void GameWorld::cancelZombieChoosed()
{
  m_zombieChoosed = false;
}

bool GameWorld::isZombieChoosed()
{
  return m_zombieChoosed;
}

bool GameWorld::placeZombie(int row, int col)
{
  if (m_choosedZombieType == ZombieType::BUNGEE)
  {
    if (!ifPlantAt(col, row))
      return false;
  }
  else if (col < m_deploymentStartCol || ifPlantAt(col, row))
  {
    return false;
  }
  if (consumeSun(getPriceByType(m_choosedZombieType)))
  {
    switch (m_choosedZombieType)
    {
    case ZombieType::REGULAR:
    {
      std::shared_ptr<RegularZombie> zombie = std::make_shared<RegularZombie>();
      zombie->setLocation(col, row);
      m_waitingObjects.push_back(zombie);
      std::shared_ptr<CardHover> hover = std::make_shared<CardHover>();
      hover->setLoc(m_choosedZombieType);
      m_waitingObjects.push_back(hover);
      break;
    }
    case ZombieType::CONEHEAD:
    {
      std::shared_ptr<ConeheadZombie> zombie = std::make_shared<ConeheadZombie>();
      zombie->setLocation(col, row);
      m_waitingObjects.push_back(zombie);
      std::shared_ptr<CardHover> hover = std::make_shared<CardHover>();
      hover->setLoc(m_choosedZombieType);
      m_waitingObjects.push_back(hover);
      break;
    }
    case ZombieType::BUCKET:
    {
      std::shared_ptr<BucketZombie> zombie = std::make_shared<BucketZombie>();
      zombie->setLocation(col, row);
      m_waitingObjects.push_back(zombie);
      std::shared_ptr<CardHover> hover = std::make_shared<CardHover>();
      hover->setLoc(m_choosedZombieType);
      m_waitingObjects.push_back(hover);
      break;
    }
    case ZombieType::POLE:
    {
      std::shared_ptr<PoleZombie> zombie = std::make_shared<PoleZombie>();
      zombie->setLocation(col, row);
      m_waitingObjects.push_back(zombie);
      std::shared_ptr<CardHover> hover = std::make_shared<CardHover>();
      hover->setLoc(m_choosedZombieType);
      m_waitingObjects.push_back(hover);
      break;
    }
    case ZombieType::BUNGEE:
    {
      std::shared_ptr<BungeeZombie> zombie = std::make_shared<BungeeZombie>();
      zombie->setBungeeLocation(col, row);
      m_waitingObjects.push_back(zombie);
      std::shared_ptr<CardHover> hover = std::make_shared<CardHover>();
      hover->setLoc(m_choosedZombieType);
      m_waitingObjects.push_back(hover);
      break;
    }
    }
  }
  else
  {
    return false;
  }
  return true;
}

std::list<std::shared_ptr<GameObject>> GameWorld::getObjects()
{
  return m_objects;
}