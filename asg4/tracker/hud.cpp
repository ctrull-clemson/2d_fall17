#include <SDL_image.h>
#include "ioMod.h"
#include "hud.h"
#include "gamedata.h"
#include "renderContext.h"
#include "gamedata.h"

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
  io(IOmod::getInstance()),
  loc_x(Gamedata::getInstance().getXmlInt("hud/loc_x") ),
  loc_y(Gamedata::getInstance().getXmlInt("hud/loc_y") )
{}

void HUD::draw(){
  if(drawHUD)
  {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_Rect r({loc_x, loc_y, 200, 92});
    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 220, 220, 220, 255 );
    SDL_Rect r2({(loc_x + 4), (loc_y + 4), 192, 84});
    SDL_RenderFillRect( renderer, &r2 );

    io.writeText("HUD:", (loc_x + 8), (loc_y + 5));
    io.writeText(movement, (loc_x + 8), (loc_y + 30));
    io.writeText(shooting, (loc_x + 8), (loc_y + 55));
  }
}

void HUD::setDrawBool(bool changeTo)
{
  drawHUD = changeTo;
  alreadyChanged = true;
}

bool HUD::getDrawBool()
{
  return drawHUD;
}

bool HUD::getAlreadyBool()
{
  return alreadyChanged;
}
