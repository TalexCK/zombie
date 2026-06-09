#include "pvz/Objects/Brain.hpp"

Brain::Brain()
    : GameObject(ImageID::BRAIN_ICON, 35, FIRST_ROW_CENTER, LayerID::UI,
                 32, 31, AnimID::NO_ANIMATION)
{
}

void Brain::Update() {}
void Brain::OnClick() {}

void Brain::setID(int id)
{
  this->m_id = id;
  MoveTo(35, FIRST_ROW_CENTER + m_id * LAWN_GRID_HEIGHT);
}

void Brain::die()
{
  live = false;
}

bool Brain::isLive()
{
  return live;
}