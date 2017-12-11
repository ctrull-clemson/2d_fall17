#include <SDL_image.h>
#include "ioMod.h"
#include "gamestat_hud.h"
#include "gamedata.h"
#include "renderContext.h"
#include "gamedata.h"

GameHUD& GameHUD::getInstance() {
  static GameHUD instance;
  return instance;
}

GameHUD::~GameHUD() {
}

GameHUD::GameHUD() :
  gameStatHeaders(),
  renderer( RenderContext::getInstance()->getRenderer() ),
  io(IOmod::getInstance()),
  loc_x(Gamedata::getInstance().getXmlInt("gamestat_hud/loc_x") ),
  loc_y(Gamedata::getInstance().getXmlInt("gamestat_hud/loc_y") )
{
  gameStatHeaders.push_back("GAME STATS");
  gameStatHeaders.push_back("Timer: ");
  gameStatHeaders.push_back("Dogs Rescued: ");
  gameStatHeaders.push_back("Dogs Remaining: ");
  gameStatHeaders.push_back("Empty Houses: ");
}

void GameHUD::draw(const unsigned int timer, unsigned int rescued, unsigned int remaining, unsigned int houses, bool gameFinished){
  int window_w = 225;
  int window_h = (int)(17 + ((gameStatHeaders.size()) * 25));

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_Rect r({loc_x, loc_y, window_w, window_h});
  SDL_RenderFillRect( renderer, &r );

  SDL_SetRenderDrawColor( renderer, 220, 220, 220, 255 );
  SDL_Rect r2({(loc_x + 4), (loc_y + 4), (window_w - 8), (window_h - 8)});
  SDL_RenderFillRect( renderer, &r2 );

  io.writeText(gameStatHeaders[0], (loc_x + 8), (loc_y + 5));
  if(gameFinished)
  {
    io.writeText(gameStatHeaders[1] + std::to_string((unsigned int) (timer / 1000)), (loc_x + 8), (loc_y + 25), {0,0,255,255}); // Timer
  }
  else
  {
    io.writeText(gameStatHeaders[1] + std::to_string((unsigned int) (timer / 1000)), (loc_x + 8), (loc_y + 25)); // Timer
  }
  io.writeText((gameStatHeaders[2] + std::to_string(rescued)), (loc_x + 8), (loc_y + 25 * 2)); // Dogs Rescued
  io.writeText((gameStatHeaders[3] + std::to_string(remaining)), (loc_x + 8), (loc_y + 25 * 3)); // Dogs Remaining
  io.writeText((gameStatHeaders[4] + std::to_string(houses)), (loc_x + 8), (loc_y + 25 * 4)); // Empty Houses Remaining
}
