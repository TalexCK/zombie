#include "pvz/Zombies/ConeheadZombie.hpp"

ConeheadZombie::ConeheadZombie()
    : Zombie(ImageID::CONEHEAD_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::WALK, 640)
{
}

void ConeheadZombie::Update() {}
void ConeheadZombie::OnClick() {}
