#pragma once

#include <anim/Anim.hpp>
/** Frames that are for things that don't change */

struct {
  AnimFrame SCRAP = {{16, 0, 16, 16}, -1, nullptr, 0, 0};
  AnimFrame TOWER = {{0, 0, 32, 64}, -1, nullptr, 0, 0};
  AnimFrame ROCK = {{0, 0, 8, 8}, -1, nullptr, -4, -4};
} NotMovingAnim;
