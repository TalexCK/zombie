#ifndef REPEATER_HPP
#define REPEATER_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Repeater : public GameObject
{
public:
  Repeater();

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

#endif // !REPEATER_HPP