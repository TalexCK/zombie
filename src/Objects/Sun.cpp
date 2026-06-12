#include "pvz/Objects/Sun.hpp"

#include "pvz/utils.hpp"

Sun::Sun()
    : GameObject(ImageID::SUN, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::SUN,
                 SUN_SIZE, SUN_SIZE, AnimID::IDLE)
{
  setSun();
}

void Sun::Update() {}
void Sun::OnClick()
{
  if_live = false;
}

void Sun::setPosition(int x, int y)
{
  m_x = x + randInt(0, SUN_SCATTER_DIAMETER) - SUN_SCATTER_RADIUS;
  m_y = y + randInt(0, SUN_SCATTER_DIAMETER) - SUN_SCATTER_RADIUS;
  MoveTo(m_x, m_y);
}
