#include "pvz/Zombies/RegularZombie.hpp"

RegularZombie::RegularZombie()
    : GameObject(ImageID::REGULAR_ZOMBIE, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::ZOMBIES,
                 20, 80, AnimID::WALK)
{
}

void RegularZombie::Update() {}
void RegularZombie::OnClick() {}

void RegularZombie::setLocation(int col, int row)
{
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT);
}