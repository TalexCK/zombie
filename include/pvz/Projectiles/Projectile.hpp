#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

#include "pvz/GameWorld/GameWorld.hpp"

class Projectile : public GameObject
{
public:
  Projectile(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
  virtual ~Projectile() = default;

  virtual void Update() = 0;
  virtual void OnClick() = 0;
  void kill();
};

#endif // !PROJECTILE_HPP