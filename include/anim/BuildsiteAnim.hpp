#pragma once

#include <anim/Anim.hpp>

struct {
  AnimFrame BUILD1 = {{0, 0, 32, 64}, -1, &BUILD2};
  AnimFrame BUILD2 = {{1 * 32, 0, 32, 64}, -1, &BUILD3};
  AnimFrame BUILD3 = {{2 * 32, 0, 32, 64}, -1, &BUILD4};
  AnimFrame BUILD4 = {{3 * 32, 0, 32, 64}, -1, nullptr};
} bs_TowerAnim;
