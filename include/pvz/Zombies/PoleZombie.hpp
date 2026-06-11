#ifndef POLEZOMBIE_HPP
#define POLEZOMBIE_HPP

#include "pvz/utils.hpp"
#include "pvz/Zombies/Zombie.hpp"

class PoleZombie : public Zombie
{
public:
  PoleZombie();

  void Update() override;

  bool ifRunning() const;

  void shouldJump();
  bool ifJumpping() const;
  bool attackPlant(Plant &plant) override;
  void afterCollisionCheck() override;

private:
  bool m_running = true;
  int frame_count = 41;
};

#endif // !POLEZOMBIE_HPP
