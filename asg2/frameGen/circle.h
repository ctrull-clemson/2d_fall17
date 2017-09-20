#include <string>
#include <SDL.h>

class Circle {
public:
  Circle(SDL_Renderer*, int, SDL_Point, SDL_Color); // Render, radius, center point, color
  void draw();
  void drawHalf();

private:
  SDL_Renderer* const renderer;
  const int RADIUS;
  const SDL_Point CENTER;
  const SDL_Color CIRCLE_COLOR;
  Circle(const Circle&);
};

//FrameGenerator& operator=(const FrameGenerator&);
