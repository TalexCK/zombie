#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

#include "pvz/Objects/ZombieCard.hpp"

class Plant;

class Zombie : public GameObject
{
public:
  Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);
  virtual ~Zombie() = default;

  void Update() override;
  void OnClick() override;

  void setLocation(int col, int row);

  bool isEating() const;
  void setEating(bool eating);

  void decreaseHp(int hp);
  virtual bool attackPlant(Plant &plant);
  virtual void afterCollisionCheck();

  void setZombieType(ZombieType zombieType);

  ZombieType getZombieType();

protected:
  void moveZombie();

  int m_hp = REGULAR_ZOMBIE_HP;
  bool m_eating = false;
  AnimID m_currentAnim = AnimID::WALK;
  ZombieType m_zombieType;
};

#endif // !ZOMBIE_HPP
