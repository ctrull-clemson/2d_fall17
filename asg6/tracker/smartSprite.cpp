#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

void SmartSprite::goLeft()
{
  currentDirection = LEFT;
  if(currentMode == EVADE)
  {
    centerPoint[0] = std::max(centerPoint[0] - runRange, runRange);
  }
  if((getX() < 5) && (std::abs(playerPos[0] - centerPoint[0]) < (safeDistance + runRange)))
  {
    setX(worldWidth-getScaledWidth());
    centerPoint[0] = getX() - (runRange + 1);
  }

  setVelocityX( -abs(getVelocityX()) );
  images = imagesLeft;
}
void SmartSprite::goRight()
{
  currentDirection = RIGHT;
  if(currentMode == EVADE)
  {
    centerPoint[0] = std::min(centerPoint[0] + runRange, worldWidth - runRange);
  }

  if((getX() > worldWidth - 5)
        && (std::abs(playerPos[0] - centerPoint[0]) < (safeDistance + runRange)))
  {
    setX(0);
    centerPoint[0] = runRange + 1;
  }

  setVelocityX( fabs(getVelocityX()));
  images = imagesRight;
}
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }

void SmartSprite::updateSleepTimer(unsigned int reduce)
{
  if(sleepTimer < reduce)
  {
    sleepTimer = 0;
  }
  else
  {
    sleepTimer =  sleepTimer - reduce;
  }
}

SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos,
  int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(NORMAL),
  currentDirection(RIGHT),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  runRange(Gamedata::getInstance().getXmlFloat(name+"/runRange")),
  sleepTimer(0),
  centerPoint(pos),
  imagesIdleRight( ImageFactory::getInstance().getImages(name + "IdleRight") ),
  imagesIdleLeft( ImageFactory::getInstance().getImages(name + "IdleLeft") )
{}

SmartSprite::SmartSprite(const SmartSprite& s) :
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  currentDirection(s.currentDirection),
  safeDistance(s.safeDistance),
  runRange(s.runRange),
  sleepTimer(s.sleepTimer),
  centerPoint(s.centerPoint),
  imagesIdleRight(s.imagesIdleRight),
  imagesIdleLeft(s.imagesIdleLeft)
{}

void SmartSprite::update(Uint32 ticks) {
  updateSleepTimer(ticks);
  if(sleepTimer > 0)
  {
    if(currentDirection == RIGHT)
    {
      images = imagesIdleRight;
    }
    else if (currentDirection == LEFT)
    {
      images = imagesIdleLeft;
    }
    advanceFrame(ticks);
    return;
  }
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0];
  float ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(std::abs(distanceToEnemy) < safeDistance) currentMode = EVADE;

    // Check if within runRange
    if(std::abs(x - centerPoint[0]) > runRange)
    {
      // Turn around
      if(x < centerPoint[0]) { goRight(); }
      else { goLeft(); }
    }
  }
  else if  ( currentMode == EVADE ) {
    if(std::abs(distanceToEnemy) > safeDistance) currentMode=NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
}
