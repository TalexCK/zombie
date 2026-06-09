#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/Objects/Background.hpp"
#include "pvz/Objects/ProgressBar.hpp"

void GameWorld::Init()
{
  m_objects.clear();
  m_objects.push_back(std::make_shared<Background>());

  updateStage();
  addSun(150);
  initBrains();
  m_sunText = std::make_shared<TextBase>(SUN_COUNTER_X, SUN_COUNTER_Y);
  m_sunText->SetText(std::to_string(getSunCount()));
  m_sunText->SetColor(0, 0, 0);

  m_infoText = std::make_shared<TextBase>(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 40);
  m_infoText->SetText("Stage " + std::to_string(m_stage) + "/" + std::to_string(TOTAL_ROUNDS) + "  Brains: " + std::to_string(m_brains));
  m_infoText->SetColor(255, 255, 255);

  m_progressBar = std::make_shared<ProgressBar>();
  m_objects.push_back(m_progressBar);
  m_progressBar->setStage(m_stage);
}

LevelStatus GameWorld::Update()
{
  // YOUR CODE HERE
  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp()
{
  // YOUR CODE HERE
}
