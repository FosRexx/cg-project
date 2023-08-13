#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "sdlGraphics.h"
#include "worldMap.h"
#include "bresenhamLineDrawingAlgorith.h"

void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY);

#endif
