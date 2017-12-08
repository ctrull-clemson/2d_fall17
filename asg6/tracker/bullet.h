#include <iostream>
#include "sprite.h"
#include "gamedata.h"
#include "explodingSprite.h"

class Bullet : public Sprite {
public:
  explicit Bullet(const string& name) :
    Sprite(name),
    distance(0),
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
    tooFar(false),
    explosion(),
    doneExploding(false)
  { }
  virtual void update(Uint32 ticks);
  virtual void draw() const;
  bool goneTooFar() const { return tooFar; }
  bool isDoneExploding() const { return doneExploding; }
  void explode() { if ( !explosion ) explosion = new ExplodingSprite(*this); };
  void reset() {
    tooFar = false;
    distance = 0;
    doneExploding = false;
  }

private:
  float distance;
  float maxDistance;
  bool tooFar;
  ExplodingSprite * explosion;
  bool doneExploding;
  Bullet(const Bullet&) = delete;  
  Bullet& operator=(const Bullet&);
};
