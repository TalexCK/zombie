#include "pvz/Objects/RedLine.hpp"

RedLine::RedLine()
    : GameObject(ImageID::RED_LINE, LAWN_GRID_LEFT + RED_LINE_INITIAL_COL * LAWN_GRID_WIDTH,
                 WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR - RED_LINE_Y_OFFSET, LayerID::UI,
                 0, 0, AnimID::NO_ANIMATION)
{
}

void RedLine::Update() {}
void RedLine::OnClick() {}

void RedLine::updateColLeft(int col)
{
  m_colLeft = col;
  MoveTo(LAWN_GRID_LEFT + m_colLeft * LAWN_GRID_WIDTH, WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR - RED_LINE_Y_OFFSET);
}
