#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"

#include "pvz/GameObject/GameObject.hpp"

#include "pvz/Framework/TextBase.hpp"

#include "pvz/Objects/ProgressBar.hpp"
#include "pvz/Objects/RedLine.hpp"
#include "pvz/utils.hpp"

class GameWorld : public WorldBase
{
public:
  // Consider:
  // Use shared_from_this() instead of "this" to create a pointer to oneself?
  // Use unique_ptr<> / shared_ptr<> to manage GameObjects?
  GameWorld() = default;
  ~GameWorld() = default;

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  int getSunCount() const;

  void addSun(int count);

  bool consumeSun(int count);

  bool decreaseBrains();

  bool updateStage();

  void initBrains();

  void initZombieCards();

  void initZombiePlaces();

  bool setAsPlantAt(int x, int y);

  bool removeAsPlantAt(int x, int y);

  bool ifPlantAt(int x, int y) const;

  void generatePlant(int cols);

private:
  std::list<std::shared_ptr<GameObject>> m_objects;
  int m_sunCount = 0;
  int m_stage = 0;
  int m_brains = 0;
  std::shared_ptr<TextBase> m_sunText;
  std::shared_ptr<TextBase> m_infoText;
  std::shared_ptr<ProgressBar> m_progressBar;
  std::shared_ptr<RedLine> m_redLine;

  int m_blocks[GAME_ROWS * GAME_COLS] = {0};

  int m_deploymentStartCol = INITIAL_ZOMBIE_DEPLOYMENT_START_COL + ZOMBIE_DEPLOYMENT_BUFFER_COLS;
};

#endif // !GAMEWORLD_HPP__
