#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class BulletHUD {
public:
  static BulletHUD& getInstance();
  ~BulletHUD();
  void draw(unsigned int shot, unsigned int total);
  void setDrawBool(bool input);
  bool getDrawBool();
  bool getAlreadyBool();

private:
  std::string available_text;
  std::string total_text;
  SDL_Renderer* renderer;
  const IOmod& io;

  bool drawHUD = true;
  bool alreadyChanged = false;

  int loc_x;
  int loc_y;

  BulletHUD();
  BulletHUD(const BulletHUD&);
  BulletHUD& operator=(const BulletHUD&);
};
