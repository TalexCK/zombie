#ifndef ZOMBIEPLACE_HPP
#define ZOMBIEPLACE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class ZombiePlace : public GameObject
{
public:
  ZombiePlace();

  void Update() override;
  void OnClick() override;

  void setPosition(int row, int col);
};

#endif // !ZOMBIEPLACE_HPP