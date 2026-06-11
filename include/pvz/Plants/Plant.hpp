#ifndef PLANT_HPP
#define PLANT_HPP
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Plant : public GameObject
{
public:
  Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);
  virtual ~Plant() = default;

  virtual void Update() = 0;
  virtual void OnClick() = 0;

  void setPosition(int row, int col);

  void decreaseHp(int damage);

  void setHp(int hp);

  void setGameWorld(std::shared_ptr<GameWorld> world);

protected:
  int m_row = 0;
  int m_col = 0;
  int m_hp = 100;
  std::shared_ptr<GameWorld> m_world;
};

#endif // !PLANT_HPP