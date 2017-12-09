#ifndef HOUSE__H
#define HOUSE__H

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class House : public Drawable {
public:
  House(const std::string&);
  House(const House&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return images[haveDog];
  }
  int getScaledWidth()  const {
    return getScale()*images[haveDog]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[haveDog]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[haveDog]->getSurface();
  }

  void setStatus(bool input) { haveDog = input; }

protected:
  std::vector<Image *> images;

  bool haveDog;
  unsigned numberOfFrames;
  int worldWidth;
  int worldHeight;

  void switchFrame(Uint32 ticks);
  House& operator=(const House&);
};

#endif
