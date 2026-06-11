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
  auto world = m_world.lock();
  if (!world)
    return;
  if (world->isZombieChoosed())
  {
    world->cancelZombieChoosed();
  }
  else
  {
    if (world->getSunCount() >= getPriceByType(m_type))
    {
      world->setZombieChoosed(m_type);
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
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_CONEHEAD_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUCKET:
    ChangeImage(ImageID::ZOMBIE_CARD_BUCKET);
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_BUCKET_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::POLE:
    ChangeImage(ImageID::ZOMBIE_CARD_POLE);
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_POLE_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  case ZombieType::BUNGEE:
    ChangeImage(ImageID::ZOMBIE_CARD_BUNGEE);
    MoveTo(ZOMBIE_CARD_FIRST_X + ZOMBIE_CARD_BUNGEE_SLOT * ZOMBIE_CARD_SPACING, ZOMBIE_CARD_Y);
    break;
  }
}

int getPriceByType(ZombieType type)
{
  switch (type)
  {
  case ZombieType::REGULAR:
    return REGULAR_ZOMBIE_PRICE;
  case ZombieType::CONEHEAD:
    return CONEHEAD_ZOMBIE_PRICE;
  case ZombieType::BUCKET:
    return BUCKET_ZOMBIE_PRICE;
  case ZombieType::POLE:
    return POLE_ZOMBIE_PRICE;
  case ZombieType::BUNGEE:
    return BUNGEE_ZOMBIE_PRICE;
  default:
    return UNKNOWN_ZOMBIE_PRICE;
  }
}

int getFreezeByType(ZombieType type)
{
  switch (type)
  {
  case ZombieType::REGULAR:
    return ZOMBIE_CARD_COOLDOWN_TICKS;
  case ZombieType::CONEHEAD:
    return ZOMBIE_CARD_COOLDOWN_TICKS;
  case ZombieType::BUCKET:
    return ZOMBIE_CARD_COOLDOWN_TICKS;
  case ZombieType::POLE:
    return ZOMBIE_CARD_COOLDOWN_TICKS;
  case ZombieType::BUNGEE:
    return ZOMBIE_CARD_COOLDOWN_TICKS;
  default:
    return NO_ZOMBIE_CARD_COOLDOWN_TICKS;
  }
}

void ZombieCard::setGameWorld(std::shared_ptr<GameWorld> world)
{
  m_world = world;
}
