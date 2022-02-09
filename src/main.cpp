#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "Input.hpp"

int main(int argc, char** argv)
{
  SDL_Log("SDL init...");

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl init failed with error: %s", SDL_GetError());
    return EXIT_FAILURE;
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  int imgInitted = IMG_Init(imgFlags);

  if((imgInitted&imgFlags) != imgFlags)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl img init failed with error: %s", IMG_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow("SDL2 MACOS SETUP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(window == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create window failed with error: %s", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if(renderer == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl create renderer failed with error: %s", SDL_GetError());
    return EXIT_FAILURE;
  }

  int width = 100;
  int height = 100;
  SDL_Rect object = { (WINDOW_WIDTH / 2) - (width / 2), (WINDOW_HEIGHT / 2) - (height / 2), width, height };

  while(Input::Instance()->Listen())
  {
    Input::Instance()->Demo();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderFillRect(renderer, &object);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();

  SDL_Log("SDL quit.");

  return EXIT_SUCCESS;
}
