#include <util/DrawFns.h>

void DrawFns::RenderCircle(SDL_Renderer *renderer, float x, float y,
                           float radius) {
  const float diameter = (radius * 2);

  float px = (radius - 1);
  float py = 0;
  float tx = 1;
  float ty = 1;
  float error = (tx - diameter);

  while (px >= py) {
    //  Each of the following renders an octant of the circle
    SDL_RenderPoint(renderer, x + px, y - py);
    SDL_RenderPoint(renderer, x + px, y + py);
    SDL_RenderPoint(renderer, x - px, y - py);
    SDL_RenderPoint(renderer, x - px, y + py);
    SDL_RenderPoint(renderer, x + py, y - px);
    SDL_RenderPoint(renderer, x + py, y + px);
    SDL_RenderPoint(renderer, x - py, y - px);
    SDL_RenderPoint(renderer, x - py, y + px);

    if (error <= 0) {
      ++py;
      error += ty;
      ty += 2;
    }

    if (error > 0) {
      --px;
      tx += 2;
      error += (tx - diameter);
    }
  }
}
