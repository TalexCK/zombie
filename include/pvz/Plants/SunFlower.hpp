#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class SunFlower : public GameObject
{
public:
  SunFlower();

  void Update() override;
  void OnClick() override;

  void setPosition(int row, int col);

private:
  int m_row = 0;
  int m_col = 0;
};

#endif // !SUNFLOWER_HPP