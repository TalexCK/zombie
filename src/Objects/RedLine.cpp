#include "pvz/Objects/RedLine.hpp"

RedLine::RedLine()
    : GameObject(ImageID::RED_LINE, LAWN_GRID_LEFT + 2 * LAWN_GRID_WIDTH, WINDOW_HEIGHT / 2 - 30, LayerID::UI,
                 0, 0, AnimID::NO_ANIMATION)
{
}

void RedLine::Update() {}
void RedLine::OnClick() {}

void RedLine::updateColLeft(int col)
{
  m_colLeft = col;
  MoveTo(LAWN_GRID_LEFT + m_colLeft * LAWN_GRID_WIDTH, WINDOW_HEIGHT / 2 - 30);
}