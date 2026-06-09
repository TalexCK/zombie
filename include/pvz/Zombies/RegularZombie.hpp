#ifndef REGULARZOMBIE_HPP
#define REGULARZOMBIE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class RegularZombie : public GameObject
{
public:
  RegularZombie();

  void Update() override;
  void OnClick() override;

  void setLocation(int col, int row);

private:
  int hp = 260;
};

#endif // !REGULARZOMBIE_HPP