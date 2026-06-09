cmake_minimum_required(VERSION 3.16)

add_library(
  Objects
  STATIC
  Background.cpp
  ProgressBar.cpp
  Brain.cpp
  RedLine.cpp
  ZombieCard.cpp
  ZombiePlace.cpp
  CardHover.cpp
)

target_link_libraries(
  Objects
  PUBLIC
  GameObject
)
