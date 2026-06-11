#ifndef PEA_HPP
#define PEA_HPP
#include "pvz/Projectiles/Projectile.hpp"
#include "pvz/utils.hpp"

class Pea : public Projectile
{
public:
  Pea();
  void Update() override;

  void setPosition(int col, int row);
  bool isActive() const override;
  int getDamage() const override;
  void deactive() override;

private:
  bool active = true;
};

#endif // !PEA_HPP