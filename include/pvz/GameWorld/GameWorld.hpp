#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "pvz/Framework/WorldBase.hpp"

#include "pvz/GameObject/GameObject.hpp"

#include "pvz/Framework/TextBase.hpp"

#include "pvz/Objects/ProgressBar.hpp"
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

  int getSunCount() const { return m_sunCount; }
  void addSun(int count)
  {
    m_sunCount += count;
  }
  bool consumeSun(int count)
  {
    if (m_sunCount < count)
      return false;
    m_sunCount -= count;
    return true;
  }

  bool decreaseBrains()
  {
    m_brains--;
    if (m_brains <= 0)
      return true;
    return false;
  }

  bool updateStage()
  {
    m_stage++;
    if (m_stage > TOTAL_ROUNDS)
      return false;
    return true;
  }

  void initBrains()
  {
    m_brains = 5;
  }

private:
  std::list<std::shared_ptr<GameObject>> m_objects;
  int m_sunCount = 0;
  int m_stage = 0;
  int m_brains = 0;
  std::shared_ptr<TextBase> m_sunText;
  std::shared_ptr<TextBase> m_infoText;
  std::shared_ptr<ProgressBar> m_progressBar;
};

#endif // !GAMEWORLD_HPP__
