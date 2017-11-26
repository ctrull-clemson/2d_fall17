#ifndef PLAYER__H
#define PLAYER__H

#include "twowaymultisprite.h"
#include <list>
#include "smartSprite.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void up();
  void down();
  void stop();

  void attach( SmartSprite* o ) { observers.push_back(o); }
  void detach( SmartSprite* o );

protected:
  std::list<SmartSprite*> observers;

private:
  bool collision;
  Vector2f initialVelocity;
};
#endif
