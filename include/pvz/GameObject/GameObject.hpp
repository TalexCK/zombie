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
};

#endif // !GAMEOBJECT_HPP__
