#ifndef BRESENHAM_LINE_DRAWING_ALGORITHM_H
#define BRESENHAM_LINE_DRAWING_ALGORITHM_H

#include <SDL2/SDL_pixels.h>

#include "sdlGraphics.h"

void drawVerLine(int xstart, int ystart, int yend, uint32_t buffer[][SCREEN_WIDTH]);

#endif
