#ifndef REPEATER_HPP
#define REPEATER_HPP

#include "pvz/utils.hpp"
#include "pvz/Plants/Plant.hpp"

class Repeater : public Plant
{
public:
  Repeater();

  void Update() override;
  void OnClick() override;
};

#endif // !REPEATER_HPP