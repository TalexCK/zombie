#include "pvz/Objects/CardHover.hpp"

CardHover::CardHover()
    : GameObject(ImageID::COOLDOWN_MASK, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LayerID::COOLDOWN_MASK,
                 SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
{
}

void CardHover::Update()
{
  tickCounter++;
  if (tickCounter >= goalTick)
  {
    if_live = false;
  }
}
void CardHover::OnClick() {}

void CardHover::setLoc(ZombieType type)
{
  switch (type)
  {
  case ZombieType::REGULAR:
    MoveTo(ZOMBIE_CARD_FIRST_X, ZOMBIE_CARD_Y);
    break;
  case ZombieType::CONEHEAD:
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_CONEHEAD_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUCKET:
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_BUCKET_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::POLE:
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_POLE_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUNGEE:
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_BUNGEE_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  }
  tickCounter = 0;
  goalTick = getFreezeByType(type);
}
