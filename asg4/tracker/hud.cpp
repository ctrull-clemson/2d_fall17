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
  movement("- w,a,s,d to move"),
  shooting("- space to shot"),
  renderer( RenderContext::getInstance()->getRenderer() ),
  io(IOmod::getInstance())
{}

void HUD::draw(){
  if(drawHUD)
  {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_Rect r({0,0,200,92});
    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 220, 220, 220, 255 );
    SDL_Rect r2({4,4,192,84});
    SDL_RenderFillRect( renderer, &r2 );

    io.writeText("HUD:", 8, 5);
    io.writeText(movement, 8, 30);
    io.writeText(shooting, 8, 55);
  }
}

void HUD::setDrawBool(bool changeTo)
{
  drawHUD = changeTo;
}
