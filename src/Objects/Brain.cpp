#include "pvz/Objects/Brain.hpp"

Brain::Brain()
    : GameObject(ImageID::BRAIN_ICON, LAWN_GRID_LEFT, FIRST_ROW_CENTER + id * LAWN_GRID_HEIGHT, LayerID::UI,
                 2, 2, AnimID::NO_ANIMATION)
{
}

void Brain::Update() {}
void Brain::OnClick() {}

void Brain::setID(int id)
{
  this->id = id;
  MoveTo(LAWN_GRID_LEFT, FIRST_ROW_CENTER + id * LAWN_GRID_HEIGHT);
}