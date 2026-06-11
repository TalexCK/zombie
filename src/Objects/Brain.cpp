#include "pvz/Objects/Brain.hpp"

Brain::Brain()
    : GameObject(ImageID::BRAIN_ICON, BRAIN_X, FIRST_ROW_CENTER, LayerID::UI,
                 BRAIN_WIDTH, BRAIN_HEIGHT, AnimID::NO_ANIMATION)
{
  setBrain();
}

void Brain::Update() {}
void Brain::OnClick() {}

void Brain::setID(int id)
{
  this->m_id = id;
  MoveTo(BRAIN_X, FIRST_ROW_CENTER + m_id * LAWN_GRID_HEIGHT);
}

void Brain::die()
{
  if_live = false;
}

void Brain::deactive()
{
  active = false;
}

bool Brain::isActive() const
{
  return active;
}
