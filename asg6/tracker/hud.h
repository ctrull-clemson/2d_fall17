#include <vector>
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
  std::vector<std::string> hud_messages;
  SDL_Renderer* renderer;
  const IOmod& io;

  bool drawHUD = true;
  bool alreadyChanged = false;

  int loc_x;
  int loc_y;

  HUD();
  HUD(const HUD&);
  HUD& operator=(const HUD&);
};
