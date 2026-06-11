#ifndef PLANT_HPP
#define PLANT_HPP
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Plant : public GameObject
{
public:
  Plant(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);
  virtual ~Plant() = default;

  void Update() override = 0;
  void OnClick() override;

  void setPosition(int row, int col);

  void decreaseHp(int damage);

  void setHp(int hp);

  void setGameWorld(std::shared_ptr<GameWorld> world);
  virtual bool canShoot() const;
  virtual bool shouldDropSun() const;
  virtual void updateShooting(bool shooting);

protected:
  int m_row = 0;
  int m_col = 0;
  int m_hp = 100;
  std::weak_ptr<GameWorld> m_world;
};

#endif // !PLANT_HPP