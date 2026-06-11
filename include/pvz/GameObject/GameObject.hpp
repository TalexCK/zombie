#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include "pvz/Framework/ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase
{
public:
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID);
  virtual ~GameObject() = default;
  virtual void Update() = 0;
  virtual void OnClick() = 0;
  bool isLive() const;
  bool ifCrash(int x1, int y1, int x2, int y2, int width1, int height1, int width2, int height2);
  bool ifCrashObject(GameObject &other);

  bool ifZombie() const;
  bool ifPlant() const;
  bool ifSun() const;

  void setZombie();
  void setPlant();
  void setSun();

protected:
  bool if_zombie = false;
  bool if_plant = false;
  bool if_sun = false;
  bool if_live = true;
};

#endif // !GAMEOBJECT_HPP__
