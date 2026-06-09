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

  void setGameWorld(std::shared_ptr<GameWorld> world);

private:
  int m_row = 0;
  int m_col = 0;

  std::shared_ptr<GameWorld> m_world;
};

#endif // !ZOMBIEPLACE_HPP