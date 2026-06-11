#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Projectile : public GameObject
{
public:
  Projectile(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
  virtual ~Projectile() = default;

  void Update() override = 0;
  void OnClick() override;
  virtual bool isActive() const;
  virtual int getDamage() const;
  virtual void deactive();
  void kill();
};

#endif // !PROJECTILE_HPP