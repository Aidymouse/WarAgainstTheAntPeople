#pragma once

#include <anim/Anim.hpp>

struct {
  // hand.bmp
  AnimFrame HAND_NORM = {{32, 0, 32, 32}, -1, nullptr};
  AnimFrame HAND_SPLAT = {{0, 32, 32, 32}, 1, &HAND_NORM};
} ToolAnim;
