
#include <algorithm>
#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(std::list<SmartSprite*> {}),
  collision(false),
  initialVelocity(getVelocity()),
  bulletName(Gamedata::getInstance().getXmlStr(name+"/bullet")),
  bullets(),
  throwInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval"))
{ }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  observers(std::list<SmartSprite*> {}),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  bulletName(s.bulletName),
  bullets(s.bullets),
  throwInterval(s.throwInterval)
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  observers = s.observers;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::draw() const{
  TwoWayMultiSprite::draw();
  for ( const Bullet& bullet: bullets) {
    bullet.draw();
  }
}

void Player::stop() {
  setVelocity(Vector2f(0,0));
}

void Player::right() {
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]*2);
		images =  imagesRight;
  }
}
void Player::left()  {
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]*2);
    images = imagesLeft;
  }
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }

  if ( !collision ) advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  timeSinceLastFrame += ticks;
  stop();
}

void Player::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Player::throwTreat(){
  if ( timeSinceLastFrame < timeSinceLastFrame ) return;

  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:
  Bullet bullet(bulletName);
  bullet.setPosition( getPosition() +Vector2f(deltaX, deltaY) );
  bullet.setVelocity( getVelocity() );
  bullets.push_back( bullet );
  timeSinceLastFrame = 0;
}
