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
  renderer( RenderContext::getInstance()->getRenderer() ),
  io(IOmod::getInstance()),
  loc_x(Gamedata::getInstance().getXmlInt("hud/loc_x") ),
  loc_y(Gamedata::getInstance().getXmlInt("hud/loc_y") )
{
  hud_messages.push_back("- w,a,s,d to move");
  hud_messages.push_back("- space to shot");
  hud_messages.push_back("- f1 for HUD");
  hud_messages.push_back("- f2 for Bullet HUD");
}

void HUD::draw(){
  int window_w = 225;
  int window_h = (int)(17 + ((hud_messages.size() + 1) * 25));

  if(drawHUD)
  {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_Rect r({loc_x, loc_y, window_w, window_h});
    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 220, 220, 220, 255 );
    SDL_Rect r2({(loc_x + 4), (loc_y + 4), (window_w - 8), (window_h - 8)});
    SDL_RenderFillRect( renderer, &r2 );

    io.writeText("HUD:", (loc_x + 8), (loc_y + 5));

    for(unsigned int i = 0; i < hud_messages.size(); i++)
    {
      io.writeText(hud_messages[i], (loc_x + 8), (loc_y + 25 * (i + 1)));
    }
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
