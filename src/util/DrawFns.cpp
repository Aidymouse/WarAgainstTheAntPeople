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

void DrawFns::RenderFilledCircle(SDL_Renderer *renderer, float x, float y, float radius) {
    //SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
