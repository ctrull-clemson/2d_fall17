#include <string>
#include <SDL.h>

class Pokeball {
public:
  Pokeball(SDL_Renderer*, SDL_Point, int); // Render, center point, pokeball id
  void draw();

private:
  SDL_Renderer* const renderer;
  const SDL_Point CENTER;
  const int BALL_ID;
  Pokeball(const Pokeball&);
};
