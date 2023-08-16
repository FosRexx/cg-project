#ifndef RAYCASTER_H
#define RAYCASTER_H

#define texWidth 64
#define texHeight 64

#include <vector>
#include<math.h>
#include "sdlGraphics.h"
#include "worldMap.h"
#include "bresenhamLineDrawingAlgorith.h"

extern uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
extern std::vector<uint32_t> texture[8];

void generateTextures();

void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY);

#endif
