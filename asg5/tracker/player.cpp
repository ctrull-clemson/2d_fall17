
#include <algorithm>
#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(std::list<SmartSprite*> {}),
  collision(false),
  initialVelocity(getVelocity()),
  bulletName(Gamedata::getInstance().getXmlStr(name+"/bullet")),
  freeTreats(),
  thrownTreats(),
  throwInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  maxTreats(Gamedata::getInstance().getXmlInt(name+"/treatCount")),
  timeSinceLastBullet(0)
{
  for(unsigned int i = 0; i < maxTreats; i++)
  {
    freeTreats.emplace_back(bulletName);
  }
}

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  observers(std::list<SmartSprite*> {}),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  bulletName(s.bulletName),
  freeTreats(s.freeTreats),
  thrownTreats(s.thrownTreats),
  throwInterval(s.throwInterval),
  minSpeed(s.minSpeed),
  maxTreats(s.maxTreats),
  timeSinceLastBullet(s.timeSinceLastBullet)
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
  for ( const Bullet& bullet: thrownTreats) {
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

  for ( Bullet& bullet : thrownTreats ) {
    bullet.update(ticks);
    if(bullet.goneTooFar())
    {

    }
  }

  if ( !collision ) advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  timeSinceLastFrame += ticks;
  timeSinceLastBullet += ticks;
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
  if ( timeSinceLastBullet < throwInterval ) return;
  if ( freeTreats.size() == 0) return;

  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;

  // I need to add some minSpeed to velocity:
  //Bullet bullet(bulletName);

  Bullet bullet = freeTreats.front();

  bullet.setPosition( getPosition() +Vector2f(deltaX, deltaY) );
  bullet.setVelocity( getVelocity()); // + Vector2f(minSpeed, 0)

  thrownTreats.push_back( bullet );
  freeTreats.pop_front();
  timeSinceLastBullet = 0;
}
