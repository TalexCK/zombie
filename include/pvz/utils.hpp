#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <cassert>
#include <filesystem>
#include <random>
#include <string>
#include <vector>

inline std::string FindAssetDir()
{
  const std::filesystem::path cwd = std::filesystem::current_path();
  std::vector<std::filesystem::path> candidates = {
      cwd / "assets",
      cwd / "../assets",
      cwd / "../../assets",
      cwd / "attachment/assets",
  };

#ifdef PVZ_SOURCE_DIR
  candidates.push_back(std::filesystem::path(PVZ_SOURCE_DIR) / "assets");
#endif

  for (const auto &candidate : candidates)
  {
    std::error_code existsError;
    if (!std::filesystem::exists(candidate / "background.png", existsError))
    {
      continue;
    }

    std::error_code canonicalError;
    const auto canonical =
        std::filesystem::weakly_canonical(candidate, canonicalError);
    return (canonicalError ? candidate : canonical).string();
  }

  return "assets";
}

static const std::string ASSET_DIR = FindAssetDir();

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max)
{
  if (max < min)
    std::swap(max, min);
  static std::random_device rd;
  static std::mt19937 generator(rd());
  std::uniform_int_distribution<> distro(min, max);
  return distro(generator);
}

enum class LevelStatus
{
  ONGOING,
  WINNING,
  LOSING
};

enum class KeyCode
{
  NONE,
  ENTER, // Enter
  QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_CENTER_DIVISOR = 2;

const int LAWN_GRID_WIDTH = 80;
const int LAWN_GRID_HEIGHT = 100;
const int LAWN_GRID_HALF_DIVISOR = 2;

const int FIRST_ROW_CENTER = 75;
const int FIRST_COL_CENTER = 75;
const int GAME_ROWS = 5;
const int GAME_COLS = 9;
const int LAWN_GRID_LEFT = FIRST_COL_CENTER - LAWN_GRID_WIDTH / LAWN_GRID_HALF_DIVISOR;
const int LAWN_GRID_RIGHT = FIRST_COL_CENTER + (GAME_COLS - 1) * LAWN_GRID_WIDTH + LAWN_GRID_WIDTH / LAWN_GRID_HALF_DIVISOR;
const int LAWN_GRID_BOTTOM = FIRST_ROW_CENTER - LAWN_GRID_HEIGHT / LAWN_GRID_HALF_DIVISOR;
const int LAWN_GRID_TOP = FIRST_ROW_CENTER + (GAME_ROWS - 1) * LAWN_GRID_HEIGHT + LAWN_GRID_HEIGHT / LAWN_GRID_HALF_DIVISOR;
const int LAWN_GRID_CENTER_Y = (LAWN_GRID_BOTTOM + LAWN_GRID_TOP) / LAWN_GRID_HALF_DIVISOR;
const int TOTAL_ROUNDS = 5;
const int INITIAL_ZOMBIE_DEPLOYMENT_START_COL = 1;
const int FINAL_ZOMBIE_DEPLOYMENT_START_COL =
    INITIAL_ZOMBIE_DEPLOYMENT_START_COL + TOTAL_ROUNDS - 1;
const int ZOMBIE_DEPLOYMENT_BUFFER_COLS = 1;
const int ZOMBIE_DEPLOYMENT_WIDTH = LAWN_GRID_WIDTH;

const int SEED_WIDTH = 50;
const int SEED_HEIGHT = 70;
const int ZOMBIE_CARD_FIRST_X = 130;
const int ZOMBIE_CARD_SPACING = 60;
const int ZOMBIE_CARD_Y = WINDOW_HEIGHT - 44;
const int SUN_COUNTER_X = 58;
const int SUN_COUNTER_Y = WINDOW_HEIGHT - 82;
const int SUN_VALUE = 25;
const int ZOMBIE_CARD_REGULAR_SLOT = 0;
const int ZOMBIE_CARD_CONEHEAD_SLOT = 1;
const int ZOMBIE_CARD_POLE_SLOT = 2;
const int ZOMBIE_CARD_BUCKET_SLOT = 3;
const int ZOMBIE_CARD_BUNGEE_SLOT = 4;
const int REGULAR_ZOMBIE_PRICE = 50;
const int CONEHEAD_ZOMBIE_PRICE = 75;
const int BUCKET_ZOMBIE_PRICE = 125;
const int POLE_ZOMBIE_PRICE = 75;
const int BUNGEE_ZOMBIE_PRICE = 125;
const int UNKNOWN_ZOMBIE_PRICE = 0;
const int ZOMBIE_CARD_COOLDOWN_TICKS = 120;
const int NO_ZOMBIE_CARD_COOLDOWN_TICKS = 0;

const int INITIAL_SUN_COUNT = 150;
const int INFO_TEXT_X_OFFSET = 100;
const int INFO_TEXT_Y_OFFSET = 40;
const int WHITE_COLOR_COMPONENT = 255;
const int INSTANT_KILL_DAMAGE = 100000;
const int SUNFLOWER_DROP_SUN_COUNT = 6;
const int BRAINS_PER_STAGE = 5;
const int EMPTY_PLANT_BLOCK = 0;
const int OCCUPIED_PLANT_BLOCK = 1;
const int PLANT_RANDOM_TYPE_MAX = 9;
const int SUNFLOWER_RANDOM_TYPE_MAX = 3;
const int PEASHOOTER_RANDOM_TYPE_MAX = 6;
const int REPEATER_RANDOM_TYPE_MAX = 7;

const int PROGRESS_BAR_X_OFFSET = 100;
const int PROGRESS_BAR_Y = 10;
const int PROGRESS_METER_STAGE_COUNT = 8;

const int BRAIN_X = 35;
const int BRAIN_WIDTH = 32;
const int BRAIN_HEIGHT = 31;
const int RED_LINE_INITIAL_COL = 2;
const int RED_LINE_Y_OFFSET = 30;
const int ZOMBIE_PLACE_HEIGHT_OFFSET = 10;
const int SUN_SIZE = 60;
const int SUN_SCATTER_DIAMETER = 10;
const int SUN_SCATTER_RADIUS = 5;

const int PLANT_WIDTH = 60;
const int PLANT_HEIGHT = 80;
const int DEFAULT_PLANT_HP = 100;
const int BASIC_PLANT_HP = 340;
const int WALLNUT_HP = 3600;
const int WALLNUT_CRACKED_HP = 1800;
const int SHOOTER_COOLDOWN_TICKS = 32;
const int REPEATER_SECOND_SHOT_COOLDOWN_TICKS = 4;

const int PEA_SIZE = 28;
const int PEA_SPEED = 8;
const int PEA_START_X_OFFSET = 30;
const int PEA_START_Y_OFFSET = 12;
const int PEA_DAMAGE = 24;
const int NO_PROJECTILE_DAMAGE = 0;

const int HITBOX_HALF_DIVISOR = 2;
const int ZOMBIE_WIDTH = 20;
const int ZOMBIE_HEIGHT = 80;
const int REGULAR_ZOMBIE_HP = 260;
const int CONEHEAD_ZOMBIE_HP = 560;
const int BUCKET_ZOMBIE_HP = 1450;
const int POLE_ZOMBIE_HP = 420;
const int BUNGEE_ZOMBIE_HP = 450;
const int HEADGEAR_LOST_HP_THRESHOLD = 200;
const int ZOMBIE_ATTACK_DAMAGE = 4;
const int ZOMBIE_WALK_SPEED = 1;
const int ZOMBIE_LEFT_BOUNDARY_X = 35;
const int POLE_JUMP_FRAME_COUNT = 41;
const int POLE_JUMP_FORWARD_DISTANCE = 150;
const int POLE_JUMP_COLLISION_OFFSET = 40;
const int BUNGEE_INITIAL_FRAME_COUNT = 30;
const int BUNGEE_DESCENDING_STAGE = 0;
const int BUNGEE_GRABBING_STAGE = 1;
const int BUNGEE_ASCENDING_STAGE = 2;
const int BUNGEE_VERTICAL_SPEED = 6;
const int BUNGEE_TOP_ROW_SCALE = 2;
const int BUNGEE_TOP_ROW_OFFSET = 3;
const int BUNGEE_TOP_ROW_DIVISOR = 2;
const int ZOMBIE_HEIGHT_OFFSET = 20;

enum class ImageID
{
  NONE = 0,
  BACKGROUND,
  SUN,
  SHOVEL,
  COOLDOWN_MASK,
  SUNFLOWER = 10,
  PEASHOOTER,
  WALLNUT,
  REPEATER,
  WALLNUT_CRACKED,
  RED_REPEATER,
  SEED_SUNFLOWER = 20,
  SEED_PEASHOOTER,
  SEED_WALLNUT,
  SEED_REPEATER,
  SEED_RED_REPEATER,
  REGULAR_ZOMBIE = 30,
  CONEHEAD_ZOMBIE,
  BUCKET_HEAD_ZOMBIE,
  POLE_VAULTING_ZOMBIE,
  BUNGEE_ZOMBIE,
  BUNGEE_ZOMBIE_GRAB,
  PEA = 40,
  RED_PEA,
  ZOMBIES_WON = 100,
  BRAIN_ICON = 110,
  RED_LINE,
  PROGRESS_METER_EMPTY,
  PROGRESS_METER_FULL,
  PROGRESS_METER_FILL,
  PROGRESS_METER_STAGE_1,
  PROGRESS_METER_STAGE_2,
  PROGRESS_METER_STAGE_3,
  PROGRESS_METER_STAGE_4,
  PROGRESS_METER_STAGE_5,
  PROGRESS_METER_STAGE_6,
  PROGRESS_METER_STAGE_7,
  PROGRESS_METER_STAGE_8,
  ZOMBIE_CARD_REGULAR,
  ZOMBIE_CARD_CONEHEAD,
  ZOMBIE_CARD_POLE,
  ZOMBIE_CARD_BUCKET,
  ZOMBIE_CARD_BUNGEE
};

enum class AnimID
{
  NO_ANIMATION = 0,
  IDLE,
  WALK,
  EAT,
  RUN,
  JUMP
};

const int MAX_LAYERS = 8;

enum class LayerID
{
  SUN = 0,
  ZOMBIES,
  RABBIT,
  PROJECTILES,
  PLANTS,
  COOLDOWN_MASK,
  UI,
  BACKGROUND,
};

const int MS_PER_FRAME = 33;

#endif // !UTILS_HPP__
