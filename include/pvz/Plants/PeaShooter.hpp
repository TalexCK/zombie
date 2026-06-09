#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class PeaShooter : public GameObject
{
public:
  PeaShooter();

  void Update() override;
  void OnClick() override;

  void setPosition(int row, int col);

  void decreaseHP(int damage);

  bool isLive();

private:
  int m_row = 0;
  int m_col = 0;
  int hp = 100;
};

#endif // !PEASHOOTER_HPP