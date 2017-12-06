#include <iostream>
#include <cmath>
#include <functional>
#include "bullet.h"

void Bullet::update(Uint32 ticks) {
  Vector2f pos = getPosition();

  if(explosion)
  {
    explosion->update(ticks);
    if(explosion->chunkCount() == 0)
    {
      delete explosion;
      explosion = NULL;
      doneExploding = true;

      setVelocityY(0);
      setVelocityX(700);

      tooFar = false;
    }
  }

  if(tooFar)
  {
    explode();
  }
  else if(std::abs(getVelocityX()) < 15)
  {
    tooFar = true;
  }
  else
  {
    Sprite::update(ticks);
    setVelocityY(.95 * getVelocityY());
    setVelocityX(.95 * getVelocityX());
    distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
    //if (distance > maxDistance) tooFar = true;
  }

}

void Bullet::draw() const {
  if(!explosion) Sprite::draw();
  else
  {
    explosion->draw();
  }
}

/*
void Sprite::draw() const {
  if(getScale() < SCALE_EPSILON) return;
  if ( explosion ) explosion->draw();
  else image->draw(getX(), getY(), getScale());
}
*/
