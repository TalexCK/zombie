#include "pvz/Zombies/RegularZombie.hpp"

RegularZombie::RegularZombie()
    : Zombie(ImageID::REGULAR_ZOMBIE, WINDOW_WIDTH / WINDOW_CENTER_DIVISOR, WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR, LayerID::ZOMBIES,
             ZOMBIE_WIDTH, ZOMBIE_HEIGHT, AnimID::WALK, REGULAR_ZOMBIE_HP)
{
}
