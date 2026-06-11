#ifndef SHOOTER_HPP
#define SHOOTER_HPP

#include "pvz/Plants/Plant.hpp"

class Shooter : public Plant
{
public:
  Shooter(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, int hp);

  void Update() override;

  bool canShoot() const override;
  void updateShooting(bool shooting) override;

protected:
  virtual int getNextCooldown();

private:
  int cooldown = SHOOTER_COOLDOWN_TICKS;
  bool ifShooting = false;
};

#endif // !SHOOTER_HPP
