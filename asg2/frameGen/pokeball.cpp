#include <iostream>
#include <sstream>
#include <iomanip>
#include "pokeball.h"
#include "circle.h"
#include "math.h"


Pokeball::Pokeball(SDL_Renderer* rend, SDL_Point p, int id) :
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

  // Draws the top red half of the pokeball
  Circle redSemiCircle(renderer, 250, CENTER, {255,0,0,255});
  redSemiCircle.drawHalf();

  // Straight line across the middle of the pokeball
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
  int dx = 0;
  for (int i = 0; i <= 8; i++)
  {
    dx = sqrt(((256 * 256) - (i * i)));
    SDL_RenderDrawLine(renderer, (CENTER.x - dx), CENTER.y + i, (CENTER.x + dx), CENTER.y + i);
    SDL_RenderDrawLine(renderer, (CENTER.x - dx), CENTER.y - i, (CENTER.x + dx), CENTER.y - i);
  }

  // Center, circular, outer button ring
  Circle buttonOuter1(renderer, 65, CENTER, {0, 0, 0, 255});
  buttonOuter1.draw();

  // Center, circular, outer button ring
  Circle buttonOuter2(renderer, 50, CENTER, {255, 255, 255, 255});
  buttonOuter2.draw();

  // Center, circular, inside button ring
  Circle buttonInner1(renderer, 26, CENTER, {54, 54, 54, 128});
  buttonInner1.draw();

  Circle buttonInner2(renderer, 22, CENTER, {255, 255, 255, 255});
  buttonInner2.draw();
}
