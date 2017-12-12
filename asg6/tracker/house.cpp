#include "house.h"
#include "gamedata.h"
#include "renderContext.h"

House::House( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(0,0)
           ),
  images( RenderContext::getInstance()->getImages(name)),
  hasDog(true),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
  worldHeight( Gamedata::getInstance().getXmlInt("world/height") )
{ }

House::House( const std::string& name, int xLoc, int yLoc) :
  Drawable(name,
           Vector2f(xLoc, yLoc),
           Vector2f(0,0)
           ),
  images( RenderContext::getInstance()->getImages(name) ),
  hasDog(true),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
  worldHeight( Gamedata::getInstance().getXmlInt("world/height") )
{ }

House::House(const House& s) :
  Drawable(s),
	images(s.images),
	hasDog(s.hasDog),
	numberOfFrames(s.numberOfFrames),
	worldWidth(s.worldWidth),
	worldHeight(s.worldHeight)
{ }

House& House::operator=(const House& s) {
  Drawable::operator=(s);
  images = (s.images);
  hasDog = (s.hasDog);
	numberOfFrames = (s.numberOfFrames);
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void House::draw() const {
  images[hasDog]->draw(getX(), getY(), getScale());
}

void House::update(Uint32 ticks) {
  Uint32 value = ticks;
  value++;
/*
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
		images =  imagesRight;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
		images = imagesLeft;
  }
*/
}
