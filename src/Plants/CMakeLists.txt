cmake_minimum_required(VERSION 3.16)

add_library(
  Plants
  STATIC
  SunFlower.cpp
  Peashooter.cpp
  Repeater.cpp
  WallNut.cpp
)

target_link_libraries(
  Plants
  PUBLIC
  GameObject
)
