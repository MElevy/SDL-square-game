#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_timer.h"

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 750, 0);
  Uint32 render_flags = SDL_RENDERER_ACCELERATED;
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);

  SDL_Surface* square_surface = SDL_LoadBMP("assets/square.bmp");
  SDL_Texture* square_texture = SDL_CreateTextureFromSurface(renderer, square_surface);
  SDL_FreeSurface(square_surface);

  SDL_Rect square;
  SDL_QueryTexture(square_texture, NULL, NULL, &square.w, &square.h);

  square.w /= 2;
  square.h /= 2;
  square.x = (1000 - square.w) / 2;
  square.y = (750 - square.h) / 2;

  int running = 1;
  int speed = 300;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
          square.y -= speed / 30;
        } if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
          square.x -= speed / 30;
        } if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
          square.x += speed / 30;
        } if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
          square.y += speed / 30;
        }
      }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, square_texture, NULL, &square);

    SDL_RenderPresent(renderer);

    SDL_Delay(1000 / 60);
  }

  SDL_DestroyTexture(square_texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
