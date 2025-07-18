#pragma once

#include <anim/Anim.hpp>

struct {
  AnimFrame BUILD1 = {{0, 0, 32, 64}, -1, &BUILD2, -16, -64};
  AnimFrame BUILD2 = {{1 * 32, 0, 32, 64}, -1, &BUILD3, -16, -64};
  AnimFrame BUILD3 = {{2 * 32, 0, 32, 64}, -1, &BUILD4, -16, -64};
  AnimFrame BUILD4 = {{3 * 32, 0, 32, 64}, -1, nullptr, -16, -64};
} bs_TowerAnim;
