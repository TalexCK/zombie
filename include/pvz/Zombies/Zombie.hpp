#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

#include "pvz/Objects/ZombieCard.hpp"

class Zombie : public GameObject
{
public:
  Zombie(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);
  virtual ~Zombie() = default;

  virtual void Update() = 0;
  virtual void OnClick() = 0;

  void setLocation(int col, int row);

  bool isEating() const;
  void setEating(bool eating);

  void decreaseHp(int hp);

  ZombieType getZombieType() const;

protected:
  int m_hp = 260;
  bool m_eating = false;
  AnimID m_currentAnim = AnimID::WALK;
  ZombieType m_zombieType;
};

#endif // !ZOMBIE_HPP