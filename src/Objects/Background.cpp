#include "pvz/Objects/Background.hpp"

Background::Background()
    : GameObject(ImageID::BACKGROUND, WINDOW_WIDTH / WINDOW_CENTER_DIVISOR, WINDOW_HEIGHT / WINDOW_CENTER_DIVISOR, LayerID::BACKGROUND,
                 WINDOW_WIDTH, WINDOW_HEIGHT, AnimID::NO_ANIMATION)
{
}

void Background::Update() {}
void Background::OnClick() {}
