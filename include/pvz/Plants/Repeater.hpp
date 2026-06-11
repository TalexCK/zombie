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

  void updateShooting(bool shooting);

private:
  int cooldown = 32;
  bool ifShooting = false;
  bool ifSecond = false;
};

#endif // !REPEATER_HPP