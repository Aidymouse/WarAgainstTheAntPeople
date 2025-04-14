#pragma once

#include <anim/Anim.hpp>

struct {

  /* Normal Ant Behavior */
  // guy_sheet.bmp
  AnimFrame NORM = {{0, 0, 16, 16}, 0.3, &NORM2};
  // NORM2 = {{16, 0, 16, 16}, -1, &NORM};
  AnimFrame NORM2 = {{16, 0, 16, 16}, 0.3, &NORM};

  /** Blow Up! */
  // squish.bmp
  AnimFrame EXPLODE1 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE2 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE3 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE4 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE5 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE6 = {{0, 0, 16, 16}, 2, &NORM2};
  AnimFrame EXPLODE7 = {{0, 0, 16, 16}, 2, &NORM2};

} GuyAnim; // namespace GuyAnim
