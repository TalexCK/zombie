#ifndef ZOMBIECARD_HPP
#define ZOMBIECARD_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

enum class ZombieType
{
  REGULAR,
  BUCKET,
  BUNGEE,
  CONEHEAD,
  POLE,
};

class GameWorld;

int getPriceByType(ZombieType type);
int getFreezeByType(ZombieType type);

class ZombieCard : public GameObject
{
public:
  ZombieCard();

  void Update() override;
  void OnClick() override;

  void setType(ZombieType type);

  void setGameWorld(std::shared_ptr<GameWorld> world);

private:
  ZombieType m_type = ZombieType::REGULAR;
  std::weak_ptr<GameWorld> m_world;
};

#endif // !ZOMBIECARD_HPP