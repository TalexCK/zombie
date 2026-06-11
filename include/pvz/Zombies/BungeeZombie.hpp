#ifndef BUNGEEZOMBIE_HPP
#define BUNGEEZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class BungeeZombie : public Zombie
{
public:
  BungeeZombie();

  void Update() override;

  int getStage() const;
  void nextStage();

  void setBungeeLocation(int col, int row);
  int getFrameCount() const;
  bool attackPlant(Plant &plant) override;

private:
  int stage = 0;
  int goalY = 0;
  int goalYup = 0;
  int frame_count = BUNGEE_INITIAL_FRAME_COUNT;
};

#endif // !BUNGEEZOMBIE_HPP
