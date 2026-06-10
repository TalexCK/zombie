#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Plant.hpp"

class SunFlower : public Plant
{
public:
  SunFlower();

  void Update() override;
  void OnClick() override;
};

#endif // !SUNFLOWER_HPP