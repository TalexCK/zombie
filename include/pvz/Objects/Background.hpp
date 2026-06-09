#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Background : public GameObject
{
public:
  Background();

  void Update() override;
  void OnClick() override;
};

#endif // !BACKGROUND_HPP