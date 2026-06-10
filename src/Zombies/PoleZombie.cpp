#include "pvz/Zombies/PoleZombie.hpp"

PoleZombie::PoleZombie()
    : Zombie(ImageID::POLE_VAULTING_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::RUN, 340)
{
}

void PoleZombie::Update() {}
void PoleZombie::OnClick() {}
