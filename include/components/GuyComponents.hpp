#pragma once
// Components related to guys specifically
#include <util/Vec2.hpp>

struct g_Wandering {
  float timer = 0;
  int speed = 10;
  Vec2 dir;
};
