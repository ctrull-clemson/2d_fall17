#ifndef PLAYER__H
#define PLAYER__H

#include "twowaymultisprite.h"
#include <list>
#include "smartSprite.h"
#include "bullet.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);
  virtual void draw() const;

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
  void throwTreat();
  unsigned int getBulletCount() { return bullets.size(); }
  unsigned int getMaxBulletCount() { return maxTreats; }

protected:
  std::list<SmartSprite*> observers;

private:
  bool collision;
  Vector2f initialVelocity;

  // Shooting variables
  std::string bulletName;
  std::list<Bullet> bullets;
  float throwInterval;
  float minSpeed;
  unsigned int maxTreats;
  float timeSinceLastBullet;

};
#endif
