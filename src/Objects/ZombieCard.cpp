#include "pvz/Objects/ZombieCard.hpp"

ZombieCard::ZombieCard()
    : GameObject(ImageID::ZOMBIE_CARD_REGULAR, ZOMBIE_CARD_FIRST_X, ZOMBIE_CARD_Y, LayerID::UI,
                 SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
{
}

void ZombieCard::Update() {}
void ZombieCard::OnClick() {}

void ZombieCard::setType(ZombieType type)
{
  m_type = type;
  switch (type)
  {
  case ZombieType::REGULAR:
    ChangeImage(ImageID::ZOMBIE_CARD_REGULAR);
    MoveTo(ZOMBIE_CARD_FIRST_X, ZOMBIE_CARD_Y);
    break;
  case ZombieType::CONEHEAD:
    ChangeImage(ImageID::ZOMBIE_CARD_CONEHEAD);
    MoveTo(ZOMBIE_CARD_FIRST_X + 1 * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUCKET:
    ChangeImage(ImageID::ZOMBIE_CARD_BUCKET);
    MoveTo(ZOMBIE_CARD_FIRST_X + 3 * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::POLE:
    ChangeImage(ImageID::ZOMBIE_CARD_POLE);
    MoveTo(ZOMBIE_CARD_FIRST_X + 2 * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUNGEE:
    ChangeImage(ImageID::ZOMBIE_CARD_BUNGEE);
    MoveTo(ZOMBIE_CARD_FIRST_X + 4 * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  }
}