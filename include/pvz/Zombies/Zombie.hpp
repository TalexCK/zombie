#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Zombie : public GameObject
{
public:
  Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);
  virtual ~Zombie() = default;

  virtual void Update() = 0;
  virtual void OnClick() = 0;

  void setLocation(int col, int row);

protected:
  int m_hp = 260;
};

#endif // !ZOMBIE_HPP