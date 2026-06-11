#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Plant.hpp"

class SunFlower : public Plant
{
public:
  SunFlower();

  void Update() override;
  bool shouldDropSun() const override;
};

#endif // !SUNFLOWER_HPP