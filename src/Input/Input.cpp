#include <SDL2/SDL.h>
#include "Input.hpp"

Input* Input::_input = nullptr;

Input::Input()
{
  _keyboard = SDL_GetKeyboardState(nullptr);
  _mouseButton = 0;
}

bool Input::Listen()
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        return false;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        _keyboard = SDL_GetKeyboardState(nullptr);
        break;

      case SDL_MOUSEBUTTONDOWN:
        _mouseButton = event.button.button;
        break;

      case SDL_MOUSEBUTTONUP:
        _mouseButton = 0;
        break;

      default:
        break;
    }
  }

  return true;
}

bool Input::IsKeyDown(SDL_Scancode key)
{
  return _keyboard[key] == 1;
}

bool Input::IsMouseButtonDown(MouseButton button)
{
  if(MouseButton::LEFT == button)
  {
    return _mouseButton == SDL_BUTTON_LEFT;
  }
  if(MouseButton::RIGHT == button)
  {
    return _mouseButton == SDL_BUTTON_RIGHT;
  }
  return false;
}

void Input::Demo()
{
  if(IsKeyDown(SDL_SCANCODE_SPACE))
  {
    SDL_Log("[SPACE]");
  }
  if(IsKeyDown(SDL_SCANCODE_UP))
  {
    SDL_Log("[UP]");
  }
  if(IsKeyDown(SDL_SCANCODE_DOWN))
  {
    SDL_Log("[DOWN]");
  }
  if(IsKeyDown(SDL_SCANCODE_RIGHT))
  {
    SDL_Log("[RIGHT]");
  }
  if(IsKeyDown(SDL_SCANCODE_LEFT))
  {
    SDL_Log("[LEFT]");
  }
  if(IsMouseButtonDown(MouseButton::LEFT))
  {
    SDL_Log("[MOUSE:LEFT]");
  }
  if(IsMouseButtonDown(MouseButton::RIGHT))
  {
    SDL_Log("[MOUSE:RIGHT]");
  }
}
