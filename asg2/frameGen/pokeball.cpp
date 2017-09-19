#include <iostream>
#include <sstream>
#include <iomanip>
#include "pokeball.h"
#include "circle.h"


Pokeball::
Pokeball(SDL_Renderer* rend, SDL_Point p, int id) :
  renderer(rend),
  CENTER( p ),
  BALL_ID (id)
{}

void Pokeball::draw()
{
  // Base circle where the rest of the circles will be drawn
  Circle baseCircle(renderer, 256, CENTER, {0,0,0,255});
  baseCircle.draw();

  // Secondary circle to color bottom of pokeball
  Circle secondCircle(renderer, 250, CENTER, {255,255,255,255});
  secondCircle.draw();
}
