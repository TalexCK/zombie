#ifndef BUNGEEZOMBIE_HPP
#define BUNGEEZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class BungeeZombie : public Zombie
{
public:
  BungeeZombie();

  void Update() override;
  void OnClick() override;

  int getStage() const;
  void nextStage();

  void setBungeeLocation(int col, int row);
  int getFrameCount() const;

private:
  int stage = 0;
  int goalY = 0;
  int goalYup = 0;
  int frame_count = 30;
};

#endif // !BUNGEEZOMBIE_HPP
