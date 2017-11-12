#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "twowaymultisprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() {
  for(auto sprite : sprites)
  {
    delete sprite;
  }

  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  hud( HUD::getInstance() ),
  renderer( rc->getRenderer() ),
  mountains("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  road("road", Gamedata::getInstance().getXmlInt("road/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(std::vector<Drawable *> {}),
  currentSprite(0),
  makeVideo( false ),
  myPlayer("Dog")
{
  sprites.push_back(new Sprite("ShineSprite"));
  //sprites.push_back(new TwoWayMultiSprite("Dragon"));
  //sprites.push_back(new TwoWayMultiSprite("Dog"));
  //myPlayer = new Player("Dog");
  //Viewport::getInstance().setObjectToTrack(sprites[0]);
  Viewport::getInstance().setObjectToTrack(&myPlayer);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  mountains.draw();
  road.draw();

  for(auto sprite : sprites)
  {
    sprite->draw();
  }
  myPlayer.draw();

  viewport.draw();
  viewport.write();

  hud.draw();
  unsigned int timeCheck = clock.getTicks();
  if(timeCheck >= 3000 && timeCheck <= 3020 && !hud.getAlreadyBool())
  {
    hud.setDrawBool(false);
  }

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto sprite : sprites)
  {
    sprite->update(ticks);
  }
  myPlayer.update(ticks);

  mountains.update();
  road.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % sprites.size();

  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.setDrawBool(!hud.getDrawBool());
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
        if ( keystate[SDL_SCANCODE_W] ) {
          myPlayer.up();
        }
        if ( keystate[SDL_SCANCODE_A] ) {
          myPlayer.left();
        }
        if ( keystate[SDL_SCANCODE_S] ) {
          myPlayer.down();
        }
        if ( keystate[SDL_SCANCODE_D] ) {
          myPlayer.right();
        }

      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
