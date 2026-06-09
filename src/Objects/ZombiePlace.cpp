#include "pvz/Objects/ZombiePlace.hpp"

ZombiePlace::ZombiePlace()
    : GameObject(ImageID::NONE, 0, 0, LayerID::UI,
                 LAWN_GRID_WIDTH, LAWN_GRID_HEIGHT, AnimID::NO_ANIMATION)
{
}

void ZombiePlace::Update() {}
void ZombiePlace::OnClick() {}

void ZombiePlace::setPosition(int row, int col)
{
  m_row = row;
  m_col = col;
  MoveTo(FIRST_COL_CENTER + col * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT);
}