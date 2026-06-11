#ifndef SUN_HPP
#define SUN_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Sun : public GameObject
{
public:
  Sun();

  void Update() override;
  void OnClick() override;

  void setPosition(int x, int y);

private:
  int m_x;
  int m_y;
};

#endif // !SUN_HPP