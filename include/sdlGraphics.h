#ifndef SDL_GRAPHICS_H
#define SDL_GRAPHICS_H

#include <stdbool.h>

#include "glad/glad.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern bool isRunning;

bool initSDL();
void destroySDL();
void render();
void drawPixel(int x, int y, SDL_Color color);
/* void drawText(const char* text, int x, int y, SDL_Color color); */

#endif
