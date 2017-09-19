#include <iostream>
#include <sstream>
#include <iomanip>
#include "circle.h"

Circle::
Circle(SDL_Renderer* rend,int r, SDL_Point p, SDL_Color color) :
  renderer(rend),
  RADIUS( r ),
  CENTER( p ),
  CIRCLE_COLOR (color)
{}

void Circle::draw()
{
  SDL_SetRenderDrawColor(renderer, CIRCLE_COLOR.r, CIRCLE_COLOR.g, CIRCLE_COLOR.b, CIRCLE_COLOR.a);
  for (int w = 0; w < RADIUS * 2; w++)
  {
    for (int h = 0; h < RADIUS * 2; h++)
    {
      int dx = RADIUS - w;
      int dy = RADIUS - h;
      if ((dx*dx + dy*dy) <= (RADIUS * RADIUS)) {
        SDL_RenderDrawPoint(renderer, CENTER.x + dx, CENTER.y + dy);
      }
    }
  }
}
