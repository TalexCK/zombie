#ifndef PEA_HPP
#define PEA_HPP
#include "pvz/Projectiles/Projectile.hpp"
#include "pvz/utils.hpp"

class Pea : public Projectile
{
public:
  Pea();
  void Update() override;
  void OnClick() override;

  void setPosition(int col, int row);
};

#endif // !PEA_HPP