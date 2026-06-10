#ifndef WALLNUT_HPP
#define WALLNUT_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Plant.hpp"

class WallNut : public Plant
{
public:
  WallNut();

  void Update() override;
  void OnClick() override;
};

#endif // !WALLNUT_HPP