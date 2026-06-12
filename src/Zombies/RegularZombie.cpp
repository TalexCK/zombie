#include "pvz/Zombies/RegularZombie.hpp"

RegularZombie::RegularZombie()
    : Zombie(ImageID::REGULAR_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::WALK, REGULAR_ZOMBIE_HP)
{
    setZombieType(ZombieType::REGULAR);
}
