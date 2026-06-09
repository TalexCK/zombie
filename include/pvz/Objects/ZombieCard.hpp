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

class ZombieCard : public GameObject
{
public:
  ZombieCard();

  void Update() override;
  void OnClick() override;

  void setType(ZombieType type);

private:
  ZombieType m_type = ZombieType::REGULAR;
};

#endif // !ZOMBIECARD_HPP