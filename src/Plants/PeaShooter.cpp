#include "pvz/Plants/PeaShooter.hpp"

PeaShooter::PeaShooter()
    : Shooter(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
              60, 80, AnimID::IDLE, 340)
{
}
