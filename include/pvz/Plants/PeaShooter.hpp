#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Plant.hpp"

class PeaShooter : public Plant
{
public:
  PeaShooter();

  void Update() override;
  void OnClick() override;
};

#endif // !PEASHOOTER_HPP