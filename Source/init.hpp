#ifndef INIT_HPP_INCLUDED
#define INIT_HPP_INCLUDED
#include <SDL2/SDL.h>

void logSDLError(const char* msg);

SDL_Texture* loadTexture(const char* file, SDL_Renderer *ren);

#endif // INIT_HPP_INCLUDED
