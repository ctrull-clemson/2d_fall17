#include <SDL2/SDL.h>
#include <iostream>
#include "frameGenerator.h"
#include "circle.h"
#include "pokeball.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;


int main(void) {
  SDL_Renderer *renderer = NULL;
  SDL_Window *window;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
    WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
  );

  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, 200);

  SDL_Rect rect = {50, 50, 540, 540};
  SDL_RenderDrawRect(renderer, &rect);


  // My code to create an object of type Pokeball, and draws it.
  Pokeball myPokeball(renderer, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2}, 0);
  myPokeball.draw();
  std::cout << myPokeball;
  std::cout << std::endl;

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
