#include <SDL2/SDL.h>
#include "frameGenerator.h"
#include "circle.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int main(void) {
  SDL_Renderer *renderer = NULL;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
    WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
  );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  SDL_Point center = {320, 240};
  SDL_Color color = {255,0,0,255};
  Circle myCircle(renderer, 50, center, color);
  myCircle.draw();
  //drawCircle(renderer, center, 50, color);

  SDL_RenderPresent(renderer);
  FrameGenerator frameGen(renderer, window, WINDOW_WIDTH, WINDOW_HEIGHT,
    "ctrull");
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
