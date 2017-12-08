#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "hud.h"
#include "bullet_hud.h"
#include "player.h"
#include "smartSprite.h"

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

  SDL_Renderer * const renderer;
  World mountains;
  World road;
  Viewport& viewport;

  std::vector<SmartSprite *> sprites;
  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  int currentSprite;
  bool collision;
  bool makeVideo;

  Player* myPlayer;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void printScales() const;
  void checkForCollisions();
  void checkForBulletCollisions();

  friend class Player;
};
