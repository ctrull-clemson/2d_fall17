#include <SDL_image.h>
#include "ioMod.h"
#include "hud.h"
#include "gamedata.h"
#include "renderContext.h"

HUD& HUD::getInstance() {
  static HUD instance;
  return instance;
}

HUD::~HUD() {
}

HUD::HUD() :
  movement("w,a,s,d to move"),
  shooting("space to shot (not yet implemented)"),
  renderer( RenderContext::getInstance()->getRenderer() )
{}

void HUD::draw(){
  SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

  SDL_Rect r;
  r.x = 50;
  r.y = 50;
  r.w = 150;
  r.h = 200;

  SDL_RenderFillRect( renderer, &r );

  SDL_RenderPresent(renderer);
}
