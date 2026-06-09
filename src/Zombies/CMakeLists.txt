cmake_minimum_required(VERSION 3.16)

add_library(
  Zombies
  STATIC
  RegularZombie.cpp
)

target_link_libraries(
  Zombies
  PUBLIC
  GameObject
)