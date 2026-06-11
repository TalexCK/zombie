#ifndef CARDHOVER_HPP
#define CARDHOVER_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

#include "pvz/Objects/ZombieCard.hpp"

class CardHover : public GameObject
{
public:
  CardHover();

  void Update() override;
  void OnClick() override;

  void setLoc(ZombieType type);

  bool isLive();

private:
  int tickCounter = 0;
  int goalTick = 0;
};

#endif // !CARDHOVER_HPP