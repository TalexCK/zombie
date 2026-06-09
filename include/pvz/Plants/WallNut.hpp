#ifndef WALLNUT_HPP
#define WALLNUT_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class WallNut : public GameObject
{
public:
  WallNut();

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

#endif // !WALLNUT_HPP