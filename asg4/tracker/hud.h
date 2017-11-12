#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class HUD {
public:
  static HUD& getInstance();
  ~HUD();
  void draw();

private:
  std::string movement;
  std::string shooting;
  SDL_Renderer* renderer;

  HUD();
  HUD(const HUD&);
  HUD& operator=(const HUD&);
};
