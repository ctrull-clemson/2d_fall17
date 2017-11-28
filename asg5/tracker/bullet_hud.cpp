#include <SDL_image.h>
#include "ioMod.h"
#include "bullet_hud.h"
#include "gamedata.h"
#include "renderContext.h"
#include "gamedata.h"

BulletHUD& BulletHUD::getInstance() {
  static BulletHUD instance;
  return instance;
}

BulletHUD::~BulletHUD() {
}

BulletHUD::BulletHUD() :
  available_text("Bullet List: "),
  total_text("Total Available: "),
  renderer( RenderContext::getInstance()->getRenderer() ),
  io(IOmod::getInstance()),
  loc_x(Gamedata::getInstance().getXmlInt("bullet_hud/loc_x") ),
  loc_y(Gamedata::getInstance().getXmlInt("bullet_hud/loc_y") )
{}

void BulletHUD::draw(unsigned int shot, unsigned int total){
  if(drawHUD)
  {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_Rect r({loc_x, loc_y, 200, 92});
    SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor( renderer, 220, 220, 220, 255 );
    SDL_Rect r2({(loc_x + 4), (loc_y + 4), 192, 84});
    SDL_RenderFillRect( renderer, &r2 );

    io.writeText("Bullet HUD:", (loc_x + 8), (loc_y + 5));
    io.writeText((available_text + std::to_string(shot)), (loc_x + 8), (loc_y + 30));
    io.writeText((total_text + std::to_string(total)), (loc_x + 8), (loc_y + 55));
  }
}

void BulletHUD::setDrawBool(bool changeTo)
{
  drawHUD = changeTo;
  alreadyChanged = true;
}

bool BulletHUD::getDrawBool()
{
  return drawHUD;
}

bool BulletHUD::getAlreadyBool()
{
  return alreadyChanged;
}
