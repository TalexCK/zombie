#ifndef REDLINE_HPP
#define REDLINE_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class RedLine : public GameObject
{
public:
  RedLine();

  void Update() override;
  void OnClick() override;

  void updateColLeft(int col);

private:
  int colLeft = 2;
};

#endif // !REDLINE_HPP