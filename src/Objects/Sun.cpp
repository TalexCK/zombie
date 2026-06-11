#include "pvz/Objects/Sun.hpp"

#include "pvz/utils.hpp"

Sun::Sun()
    : GameObject(ImageID::SUN, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::SUN,
                 60, 60, AnimID::IDLE)
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
  m_x = x + randInt(0, 10) - 5;
  m_y = y + randInt(0, 10) - 5;
  MoveTo(m_x, m_y);
}
