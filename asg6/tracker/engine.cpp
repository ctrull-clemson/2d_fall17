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
#include "smartSprite.h"
#include "collisionStrategy.h"

Engine::~Engine() {
  for(auto sprite : sprites)
  {
    delete sprite;
  }
  for ( CollisionStrategy* strategy : strategies ) {
    delete strategy;
  }
  for ( House* h : houses ) {
    delete h;
  }
  for ( House* eh : empty_houses ) {
    delete eh;
  }
  delete myPlayer;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  hud( HUD::getInstance() ),
  bullet_hud( BulletHUD::getInstance() ),
  game_hud( GameHUD::getInstance() ),
  renderer( rc->getRenderer() ),
  mountains("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  road("hills", Gamedata::getInstance().getXmlInt("hills/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(std::vector<SmartSprite *> {}),
  strategies(std::vector<CollisionStrategy *> {}),
  houses(std::vector<House *> {}),
  empty_houses(std::vector<House *> {}),
  currentStrategy(0),
  currentSprite(0),
  collision( false ),
  makeVideo( false ),
  myPlayer(new Player("Bowser"))
{
  srand( time( NULL ) ); //Randomize spawns, leave off until testing is good.
  strategies.push_back( new RectangularCollisionStrategy );

  // Load in all the houses
    // Get size of house, starting (x,y) for first house, spacing
  int base_x = std::abs(Gamedata::getInstance().getXmlInt("game/startLoc/x"));
  int base_y = std::abs(Gamedata::getInstance().getXmlInt("game/startLoc/y"));
  int house_x, house_y;
  int spacing = Gamedata::getInstance().getXmlInt("game/spacing") + Gamedata::getInstance().getXmlInt("House/imageWidth");
  int houseCount = std::max(1, Gamedata::getInstance().getXmlInt("game/houses"));
  int housesPerRow = (int)(houseCount/3);
  if((housesPerRow * 3) < houseCount) { housesPerRow++; }
  for(int i = 0; i < houseCount; i++)
  {
    house_x = base_x + (spacing * (i % housesPerRow));
    house_y = base_y + (spacing * (int)(i / housesPerRow));
    houses.push_back(new House("House", house_x, house_y));
  }

  // Load in all dogs
  int dogCount = std::min(Gamedata::getInstance().getXmlInt("game/dogs"), houseCount);
  std::vector<int> dogLocation;
  dogLocation.reserve(dogCount);
  for(int i = 0; i < dogCount; i++)
  {
    // Create SmartSprite dog
    sprites.push_back(new SmartSprite("Dog", myPlayer->getPosition(), 256, 123));
    myPlayer->attach( sprites[i] ); // smart sprite knows to avoid player

    // Set position of dog
    int x_offset, y_offset;
    int indexLocation = rand() % houseCount;

    // Make sure no other dog is already at the same location
    while(std::find(dogLocation.begin(), dogLocation.end(), indexLocation) != dogLocation.end())
    { indexLocation = rand() % houseCount; }
    dogLocation.push_back(indexLocation);

    x_offset = spacing * (indexLocation % housesPerRow);
    y_offset = spacing * (indexLocation % 3) + Gamedata::getInstance().getXmlInt("House/imageHeight");

    sprites[i]->setCenterPoint(Vector2f(base_x + x_offset, base_y + y_offset));
    sprites[i]->setPosition(sprites[i]->getCenterPoint());

    // Populate "empty house" list, set dog, move from houses
    int index = (rand() % houses.size());
    House * transfer = houses[index];
    transfer->setStatus(false);
    empty_houses.push_back(transfer);
    houses.erase(houses.begin() + index);
  }

  Viewport::getInstance().setObjectToTrack(myPlayer);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  mountains.draw();
  road.draw();

  for(auto h : houses) { h->draw(); }
  for(auto h : empty_houses) { h->draw(); }
  for(auto sprite : sprites) { sprite->draw(); }

  // Likely can remove this once house map is completely implemented
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  }

  myPlayer->draw();

  viewport.draw();
  viewport.write();

  hud.draw();
  bullet_hud.draw(myPlayer->getFreeCount(), myPlayer->getBulletCount());
  game_hud.draw(myPlayer->getDogsRescued(), sprites.size(), empty_houses.size());

  // Used to make HUD disappear after a few seconds.
  unsigned int timeCheck = clock.getTicks();
  if(timeCheck >= 3000 && timeCheck <= 3020 && !hud.getAlreadyBool())
  {
    hud.setDrawBool(false);
  }

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  checkForBulletCollisions(ticks);
  myPlayer->update(ticks);
  for(auto sprite : sprites)
  {
    sprite->update(ticks);
  }

  mountains.update();
  road.update();
  viewport.update(); // always update viewport last
}

// Player collision checks only
void Engine::checkForCollisions() {
  collision = false;

  // Collisions with dogs
  std::vector<SmartSprite *>::iterator ptr = sprites.begin();
  while(ptr != sprites.end()) {
    const Drawable * d = *ptr;
    if ( strategies[currentStrategy]->execute(*myPlayer, *d) ) {
      // Remove dog from the field, increase rescued dog count
      ptr = sprites.erase(ptr);
      myPlayer->rescueDog();
      delete d;
    }
    else
    {
      ptr++;
    }
  }

  // Collisions with terrain
  // Houses who are not missing a dog
  for ( const Drawable* d : houses ) {
    if ( strategies[currentStrategy]->execute(*myPlayer, *d) ) {
      collision = true;
    }
  }

  // Houses who are missing a dog
  std::vector<House *>::iterator hptr = empty_houses.begin();
  while(hptr != empty_houses.end()) {
    const Drawable * h = *hptr;
    if ( strategies[currentStrategy]->execute(*myPlayer, *h) )  {
      collision = true;
      // If player has a dog to return, then return it and update house
      if(myPlayer->getDogsRescued() > 0)
      {
        House * eh = *hptr;
        myPlayer->returnDog();
        eh->setStatus(true); // Tested & confirm does flip the house image
        houses.push_back(eh);
        hptr = empty_houses.erase(hptr);
      }

      // Unable to return a dog to this house
      else { hptr++; }
    }
    // No collision between player and empty house
    else { hptr++; }
  }

  if ( collision ) {
    myPlayer->collided();
  }
  else {
    myPlayer->missed();
    collision = false;
  }
  //std::list<Bullet> treats = myPlayer->thrownTreats;
}

void Engine::checkForBulletCollisions(Uint32 ticks) {
  std::list<Bullet *> treats = myPlayer->thrownTreats;
  for (auto d : sprites ) {
    for(auto t : treats)
    {
      if ( strategies[currentStrategy]->execute(*t, *d) ) {
        SmartSprite* dog = dynamic_cast<SmartSprite *> (d);
        if(dog && !(t->explodingNow()))
        {
          dog->setSleepTimer(t->getPotency(), ticks);
        }
        t->explode();
      }
    }
  }

  std::list<Bullet *>::iterator ptr = (myPlayer->thrownTreats).begin();
  while(ptr != (myPlayer->thrownTreats).end())
  {
    Bullet* b = *ptr;
    if(strategies[currentStrategy]->execute(*b, *myPlayer))
    {
      myPlayer->moveTreatToFree(b);
      ptr = (myPlayer->thrownTreats).erase(ptr);
    }
    else
    {
      ptr++;
    }
  }
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
        if ( keystate[SDL_SCANCODE_F2] ) {
          bullet_hud.setDrawBool(!bullet_hud.getDrawBool());
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }

      if ( keystate[SDL_SCANCODE_W] ) {
        myPlayer->up();
      }
      if ( keystate[SDL_SCANCODE_A] ) {
        myPlayer->left();
      }
      if ( keystate[SDL_SCANCODE_S] ) {
        myPlayer->down();
      }
      if ( keystate[SDL_SCANCODE_D] ) {
        myPlayer->right();
      }
      if ( keystate[SDL_SCANCODE_SPACE]){
        myPlayer->throwTreat();
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
