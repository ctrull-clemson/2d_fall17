#include <string>
#include <SDL.h>

class Pokeball {
public:
  Pokeball(SDL_Renderer*, SDL_Point, int); // Render, center point, pokeball id
  void draw();
  int getPokeballType() const;

private:
  SDL_Renderer* const renderer;
  const SDL_Point CENTER; // Center point for the pokeball
  const int BALL_ID;  // ID to determine which type of ball to draw
};

std::ostream& operator<<(std::ostream&, const Pokeball);
