#include "pvz/Objects/ZombieCard.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

ZombieCard::ZombieCard()
    : GameObject(ImageID::ZOMBIE_CARD_REGULAR, ZOMBIE_CARD_FIRST_X, ZOMBIE_CARD_Y, LayerID::UI,
                 SEED_WIDTH, SEED_HEIGHT, AnimID::NO_ANIMATION)
{
}

void ZombieCard::Update()
{
}
void ZombieCard::OnClick()
{
  if (m_world->isZombieChoosed())
  {
    m_world->cancelZombieChoosed();
  }
  else
  {
    if (m_world->getSunCount() >= getPriceByType(m_type))
    {
      m_world->setZombieChoosed(m_type);
    }
  }
}

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

int getPriceByType(ZombieType type)
{
  switch (type)
  {
  case ZombieType::REGULAR:
    return 50;
  case ZombieType::CONEHEAD:
    return 75;
  case ZombieType::BUCKET:
    return 125;
  case ZombieType::POLE:
    return 75;
  case ZombieType::BUNGEE:
    return 125;
  default:
    return 0;
  }
}

int getFreezeByType(ZombieType type)
{
  switch (type)
  {
  case ZombieType::REGULAR:
    return 120;
  case ZombieType::CONEHEAD:
    return 120;
  case ZombieType::BUCKET:
    return 120;
  case ZombieType::POLE:
    return 120;
  case ZombieType::BUNGEE:
    return 120;
  default:
    return 0;
  }
}

void ZombieCard::setGameWorld(std::shared_ptr<GameWorld> world)
{
  m_world = world;
}
