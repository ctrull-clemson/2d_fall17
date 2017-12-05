#include <iostream>
#include <cmath>
#include "bullet.h"

void Bullet::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  image->draw(getX(), getY(), getScale()); 
}

void Bullet::update(Uint32 ticks) {
  Vector2f pos = getPosition();
  if(!tooFar)
  {
    Sprite::update(ticks);
    setVelocityY(.95 * getVelocityY());
    setVelocityX(.95 * getVelocityX());
    distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
    if (distance > maxDistance) tooFar = true;
  }
}
