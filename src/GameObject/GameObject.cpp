#include "pvz/GameObject/GameObject.hpp"

GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : ObjectBase(imageID, x, y, layer, width, height, animID)
{
}

bool GameObject::ifCrash(int x1, int y1, int x2, int y2, int width1, int height1, int width2, int height2)
{
  if (x1 > x2)
  {
    int x3 = x2;
    int width3 = width2;
    x2 = x1;
    x1 = x3;
    width2 = width1;
    width1 = width3;
  }
  if (y1 > y2)
  {
    int y3 = y2;
    int height3 = height2;
    y2 = y1;
    y1 = y3;
    height2 = height1;
    height1 = height3;
  }
  return (x2 + width2 / 2 - (x1 - width1 / 2) < width1 + width2) && (y2 + height2 / 2 - (y1 - height1 / 2) < height1 + height2);
}

bool GameObject::ifCrashObject(GameObject &other)
{
  return ifCrash(GetX(), GetY(), other.GetX(), other.GetY(), GetWidth(), GetHeight(), other.GetWidth(), other.GetHeight());
}

bool GameObject::ifZombie() const
{
  return if_zombie;
}

bool GameObject::ifPlant() const
{
  return if_plant;
}

void GameObject::setZombie()
{
  if_zombie = true;
}

void GameObject::setPlant()
{
  if_plant = true;
}

bool GameObject::isLive() const
{
  return if_live;
}

bool GameObject::ifSun() const
{
  return if_sun;
}

void GameObject::setSun()
{
  if_sun = true;
}