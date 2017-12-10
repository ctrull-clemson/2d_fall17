
#include <algorithm>
#include "player.h"
#include "renderContext.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(std::list<SmartSprite*> {}),
  collision(false),
  initialVelocity(getVelocity()),
  bulletName(Gamedata::getInstance().getXmlStr(name+"/bullet")),
  freeTreats(),
  throwInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  maxTreats(Gamedata::getInstance().getXmlInt(name+"/treatCount")),
  timeSinceLastBullet(0),
  facingRight(true),
  dogsRescued(0),
  imagesUp( ImageFactory::getInstance().getImages(name + "Up") ),
  imagesDown( ImageFactory::getInstance().getImages(name + "Down")),
  thrownTreats()
{
  for(unsigned int i = 0; i < maxTreats; i++)
  {
    freeTreats.emplace_back(new Bullet(bulletName));
  }
}

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  observers(std::list<SmartSprite*> {}),
  collision(s.collision),
  initialVelocity(s.getVelocity()),
  bulletName(s.bulletName),
  freeTreats(s.freeTreats),
  throwInterval(s.throwInterval),
  minSpeed(s.minSpeed),
  maxTreats(s.maxTreats),
  timeSinceLastBullet(s.timeSinceLastBullet),
  facingRight(s.facingRight),
  dogsRescued(s.dogsRescued),
  imagesUp(s.imagesUp),
  imagesDown(s.imagesDown),
  thrownTreats(s.thrownTreats)
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
  for (auto bullet: thrownTreats) {
    bullet->draw();
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
  facingRight = true;
}
void Player::left()  {
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]*2);
    images = imagesLeft;
  }
  facingRight = false;
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
		images =  imagesUp;
  }
}
void Player::down()  {
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
		images =  imagesDown;
  }
}

void Player::update(Uint32 ticks) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }

  std::list<Bullet*>::iterator it = thrownTreats.begin();
  while(it != thrownTreats.end())
  {
    (*it)->update(ticks);
    if((*it)->isDoneExploding())
    {
      (*it)->reset();
      freeTreats.push_back(*it);
      it = thrownTreats.erase(it);
    }

    else
    {
      ++it;
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

  Bullet* bullet = freeTreats.front();

  if(!facingRight)
  {
    bullet->setPosition( getPosition() - Vector2f(deltaX, 0) );
    bullet->setVelocity( getVelocity() - Vector2f(minSpeed, 0));
  }
  else
  {
    bullet->setPosition( getPosition() + Vector2f(deltaX, 0) );
    bullet->setVelocity( getVelocity() + Vector2f(minSpeed, 0));
  }

  thrownTreats.push_back( bullet );
  freeTreats.pop_front();
  timeSinceLastBullet = 0;
}
