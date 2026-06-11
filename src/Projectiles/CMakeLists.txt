cmake_minimum_required(VERSION 3.16)

add_library(
  Projectiles
  STATIC
  Projectile.cpp
  Pea.cpp
)

target_link_libraries(
  Projectiles
  PUBLIC
  GameObject
)
