#pragma once

#include <anim/Anim.hpp>

struct {

  /* Normal Ant Behavior */
  // guy_sheet.bmp
  AnimFrame NORM = {{0, 0, 16, 16}, 0.3, &NORM2};
  // NORM2 = {{16, 0, 16, 16}, -1, &NORM};
  AnimFrame NORM2 = {{16, 0, 16, 16}, 0.3, &NORM};

  /** Squish */
  // squish.bmp
  AnimFrame SQUISH0 = {{0, 0, 16, 16}, 2, &SQUISH1};
  AnimFrame SQUISH1 = {{1 * 16, 0, 16, 16}, 0.035, &SQUISH2};
  AnimFrame SQUISH2 = {{2 * 16, 0, 16, 16}, 0.035, &SQUISH3};
  AnimFrame SQUISH3 = {{3 * 16, 0, 16, 16}, 0.035, &SQUISH4};
  AnimFrame SQUISH4 = {{4 * 16, 0, 16, 16}, 0.035, &SQUISH5};
  AnimFrame SQUISH5 = {{5 * 16, 0, 16, 16}, 0.035, &SQUISH6};
  AnimFrame SQUISH6 = {{6 * 16, 0, 16, 16}, -1, nullptr};

  /** Blow Up! */

} GuyAnim; // namespace GuyAnim
