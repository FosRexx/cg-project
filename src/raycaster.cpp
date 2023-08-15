#include "raycaster.h"

void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY) {
	// Looping through ever columns in screen
	for (int x = 0; x < SCREEN_WIDTH; x++) {
		// Calculation Ray position and direction
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // Converting x coordinate in screen into x coordinate in camera space
		double rayDirX = pDirX + cPlaneX * cameraX;
		double rayDirY = pDirY + cPlaneY * cameraX;

		// Initial position of the ray on map
		int posRayInMapX = (int)pPosX; // Since ray starts from the players position
		int posRayInMapY = (int)pPosY;

		// Length of ray from current position to the next x or y side
		double rayLengthX;
		double rayLengthY;

		// Length of ray when moving from x to next x or y to next y in unit step
		double rayUnitLengthX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX); // If rayDirX or rayDirY is 0 then set it to a very large no to represent infinity
		double rayUnitLengthY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist; // Prependicular distance between camera plane and wall

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0) {
			stepX = -1;
			rayLengthX = (pPosX - posRayInMapX) * rayUnitLengthX;
		} else {
			stepX = 1;
			rayLengthX = (posRayInMapX + 1.0 - pPosX) * rayUnitLengthX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			rayLengthY = (pPosY - posRayInMapY) * rayUnitLengthY;
		} else {
			stepY = 1;
			rayLengthY = (posRayInMapY + 1.0 - pPosY) * rayUnitLengthY;
		}

		// Performing DDA
		double maxDistance = 100.0;
		double distance = 0.0;
		while (hit == 0 && distance < maxDistance) {
			if (rayLengthX < rayLengthY) {
				posRayInMapX += stepX;
				distance = rayLengthX;
				rayLengthX += rayUnitLengthX;
				side = 0;
			} else {
				posRayInMapY += stepY;
				distance = rayLengthY;
				rayLengthY += rayUnitLengthY;
				side = 1;
			}

			if (posRayInMapX >= 0 && posRayInMapX < mapWidth && posRayInMapY >= 0 && posRayInMapY < mapHeight)
			{
				if (worldMap[posRayInMapX][posRayInMapY] > 0) 
				{
					hit = 1;
				}
			}
		}

		// Calculate the prependicular distance between the camera plane and the wall
		if (side == 0) perpWallDist = (rayLengthX - rayUnitLengthX);
		else 		   perpWallDist = (rayLengthY - rayUnitLengthY);

		int lineHeight = (int)(SCREEN_HEIGHT * 2 / perpWallDist); // Height of line to be drawn on screen

		// Calculate the start and end of vertical line
		int ystart = SCREEN_HEIGHT / 2 - lineHeight / 2;
		if (ystart < 0) ystart = 0;
		int yend = SCREEN_HEIGHT / 2 + lineHeight / 2;
		if (yend >= SCREEN_HEIGHT) yend = SCREEN_HEIGHT - 1;

		SDL_Color drawColor = {255, 255, 255, 255};
		switch (worldMap[posRayInMapX][posRayInMapY]) {
			case 1: 
				drawColor = (SDL_Color){255, 0, 0, 255}; // Red
				break;
			case 2: 
				drawColor = (SDL_Color){0, 255, 0, 255}; // Green
				break;
			case 3: 
				drawColor = (SDL_Color){0, 0, 255, 255}; // Blue
				break;
			case 4: 
				drawColor = (SDL_Color){255, 255, 255, 255}; // White
				break;
			default:
				drawColor = (SDL_Color){128, 0, 128, 255}; // Purple
				break;
		}

		if (side == 1)
			drawColor = (SDL_Color){static_cast<Uint8>(drawColor.r / 2),
				static_cast<Uint8>(drawColor.g / 2), 
				static_cast<Uint8>(drawColor.b / 2), 
				static_cast<Uint8>(drawColor.a / 2)
			};

		drawVerLine(x, ystart, yend, drawColor);
	}
}
