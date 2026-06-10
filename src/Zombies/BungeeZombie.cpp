#include "pvz/Zombies/BungeeZombie.hpp"

BungeeZombie::BungeeZombie()
    : Zombie(ImageID::BUNGEE_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
             20, 80, AnimID::JUMP, 450)
{
}

void BungeeZombie::Update() {}
void BungeeZombie::OnClick() {}
