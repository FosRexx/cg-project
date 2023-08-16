#ifndef RAYCASTER_H
#define RAYCASTER_H
#define texWidth 64
#define texHeight 64

#include "sdlGraphics.h"
#include "worldMap.h"
#include "bresenhamLineDrawingAlgorith.h"
#include<math.h>
#include<iostream>
#include<vector>

void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY);

#endif
