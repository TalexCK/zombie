#include "pvz/Plants/PeaShooter.hpp"

PeaShooter::PeaShooter()
    : Shooter(ImageID::PEASHOOTER, FIRST_ROW_CENTER, FIRST_COL_CENTER, LayerID::PLANTS,
              PLANT_WIDTH, PLANT_HEIGHT, AnimID::IDLE, BASIC_PLANT_HP)
{
}
