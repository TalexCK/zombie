#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class ProgressBar : public GameObject
{
public:
  ProgressBar();

  void Update() override;
  void OnClick() override;

  void setStage(int stage) { m_stage = stage; }

private:
  int m_stage = 0;
};

#endif // !PROGRESSBAR_HPP