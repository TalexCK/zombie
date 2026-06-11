#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Brain : public GameObject
{
public:
  Brain();

  void Update() override;
  void OnClick() override;

  void setID(int id);
  void die();

private:
  int m_id = 0;
};

#endif // !BRAIN_HPP