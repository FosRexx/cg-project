#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "sdlGraphics.h"
#include "worldMap.h"
#include "bresenhamLineDrawingAlgorith.h"
#include<math.h>
#include<iostream>
#include<math.h>
#include<vector>
#define texWidth 24
#define texHeight 24

void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY, std::vector<Uint32> (&texture)[8]);

#endif
