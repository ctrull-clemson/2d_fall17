#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "twowaymultisprite.h"
#include "math.h"

class SmartSprite : public TwoWayMultiSprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  void setCenterPoint(const Vector2f& p) { centerPoint = p; }
  const Vector2f& getCenterPoint() const    { return centerPoint; }
  void setSleepTimer(int stime, Uint32 ticks) { sleepTimer = 100 * stime + ticks; }

private:
  enum MODE {NORMAL, EVADE, ATTRACT};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  MODE currentMode;
  float safeDistance;
  float runRange;
  unsigned int sleepTimer;

  Vector2f centerPoint;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  void updateSleepTimer(unsigned int reduce);
};
#endif
