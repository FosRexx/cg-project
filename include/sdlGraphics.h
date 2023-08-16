#ifndef SDL_GRAPHICS_H
#define SDL_GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern bool isRunning;

bool initSDL();
void destroySDL();
void render();
void drawPixel(int x, int y, SDL_Color color);
void drawBuffer(uint32_t* buffer);
void drawText(const char* text, int x, int y, SDL_Color color);
void loadTextureData(std::vector<uint32_t>& texture, const char* imagePath);

#endif
