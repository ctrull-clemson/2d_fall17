#include <string>
#include <SDL.h>

class House {
public:
  House(SDL_Renderer*, int, int, SDL_Color); // Render, width, height

private:
  SDL_Renderer* const renderer;
  const int WIDTH;
  const int HEIGHT;
  const SDL_Color HOUSE_COLOR;
  House(const House&);
  //FrameGenerator& operator=(const FrameGenerator&);
};
