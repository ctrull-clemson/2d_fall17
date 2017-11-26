#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(std::list<SmartSprite*> {}),
  collision(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  observers(std::list<SmartSprite*> {}),
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  observers = s.observers;
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
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
