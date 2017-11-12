#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class HUD {
public:
  static HUD& getInstance();
  ~HUD();
  void draw();
  void setDrawBool(bool input);
  bool getDrawBool();
  bool getAlreadyBool();

private:
  std::string movement;
  std::string shooting;
  SDL_Renderer* renderer;
  const IOmod& io;

  bool drawHUD = true;
  bool alreadyChanged = false;

  HUD();
  HUD(const HUD&);
  HUD& operator=(const HUD&);
};
