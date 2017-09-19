#include <iostream>
#include <sstream>
#include <iomanip>
#include "house.h"

House::
House(SDL_Renderer* rend, int w, int h, SDL_Color color) :
  renderer(rend),
  WIDTH( w ),
  HEIGHT( h ),
  HOUSE_COLOR (color)
{}
