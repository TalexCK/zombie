#include "pvz/Objects/ProgressBar.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

static ImageID GetProgressBarImageForStage(int stage)
{
  switch (stage)
  {
  case 1:
    return ImageID::PROGRESS_METER_STAGE_1;
  case 2:
    return ImageID::PROGRESS_METER_STAGE_2;
  case 3:
    return ImageID::PROGRESS_METER_STAGE_3;
  case 4:
    return ImageID::PROGRESS_METER_STAGE_4;
  case 5:
    return ImageID::PROGRESS_METER_STAGE_5;
  case 6:
    return ImageID::PROGRESS_METER_STAGE_6;
  case 7:
    return ImageID::PROGRESS_METER_STAGE_7;
  case 8:
    return ImageID::PROGRESS_METER_STAGE_8;
  case 9:
    return ImageID::PROGRESS_METER_FULL;
  default:
    return ImageID::PROGRESS_METER_EMPTY;
  }
}

ProgressBar::ProgressBar()
    : GameObject(GetProgressBarImageForStage(1), WINDOW_WIDTH - PROGRESS_BAR_X_OFFSET, PROGRESS_BAR_Y, LayerID::UI,
                 0, 0, AnimID::NO_ANIMATION)
{
}

void ProgressBar::Update()
{
  ProgressBar::ChangeImage(GetProgressBarImageForStage(m_stage * PROGRESS_METER_STAGE_COUNT / TOTAL_ROUNDS));
}
void ProgressBar::OnClick() {}

void ProgressBar::setStage(int stage) { m_stage = stage; }
