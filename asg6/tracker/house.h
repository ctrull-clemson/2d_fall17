#ifndef HOUSE__H
#define HOUSE__H

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class House : public Drawable {
public:
  House(const std::string&);
  House(const std::string&, int, int);
  House(const House&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return images[hasDog];
  }
  int getScaledWidth()  const {
    return getScale()*images[hasDog]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[hasDog]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[hasDog]->getSurface();
  }

  void setStatus(bool input) { hasDog = input; }

protected:
  std::vector<Image *> images;

  bool hasDog;
  unsigned numberOfFrames;
  int worldWidth;
  int worldHeight;

  void switchFrame(Uint32 ticks);
  House& operator=(const House&);
};

#endif
