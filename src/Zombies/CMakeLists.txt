cmake_minimum_required(VERSION 3.16)

add_library(
  Zombies
  STATIC
  BungeeZombie.cpp
  BucketZombie.cpp
  ConeheadZombie.cpp
  PoleZombie.cpp
  RegularZombie.cpp
  Zombie.cpp
)

target_link_libraries(
  Zombies
  PUBLIC
  GameObject
)
