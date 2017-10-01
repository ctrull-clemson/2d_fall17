#include <iostream>
#include <sstream>
#include <iomanip>
#include "frameGenerator.h"

FrameGenerator::
FrameGenerator(SDL_Renderer* rend, SDL_Window*  win, int w, int h, 
               const std::string& n) :
  renderer(rend), 
  window(win), 
  WIDTH( w ),
  HEIGHT( h ),
  USERNAME( n )
{}


void FrameGenerator::makeFrame() {
  SDL_Surface* screenCap = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 
    0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  if ( screenCap ) {
    SDL_RenderReadPixels(renderer, NULL, 
      SDL_GetWindowPixelFormat(window), 
      screenCap->pixels, screenCap->pitch); 
  }
  std::stringstream strm;
  strm << "frames/" << USERNAME << ".bmp"; 
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screenCap, filename.c_str());
  SDL_FreeSurface(screenCap);
}

