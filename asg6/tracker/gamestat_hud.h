#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class GameHUD {
public:
  static GameHUD& getInstance();
  ~GameHUD();
  void draw(const unsigned int timer, unsigned int rescued, unsigned int remaining, unsigned int houses, bool gameFinished);

private:
  std::vector<std::string> gameStatHeaders;
  SDL_Renderer* renderer;
  const IOmod& io;

  int loc_x;
  int loc_y;

  GameHUD();
  GameHUD(const GameHUD&);
  GameHUD& operator=(const GameHUD&);
};
