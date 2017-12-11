#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "bullet_hud.h"
#include "gamestat_hud.h"
#include "player.h"
#include "smartSprite.h"
#include "house.h"

class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;
  HUD& hud;
  BulletHUD& bullet_hud;
  GameHUD& game_hud;

  SDL_Renderer * const renderer;
  World mountains;
  World road;
  Viewport& viewport;

  std::vector<SmartSprite *> sprites;
  std::vector<CollisionStrategy*> strategies;
  std::vector<House *> houses;
  std::vector<House *> empty_houses;
  int currentStrategy;
  int currentSprite;
  bool collision;
  bool makeVideo;
  unsigned int finalGameTime;
  bool gameFinished;

  Player* myPlayer;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void printScales() const;
  void checkForCollisions();
  void checkForBulletCollisions(Uint32 ticks);

  friend class Player;
};
