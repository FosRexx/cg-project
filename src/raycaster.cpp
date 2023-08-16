#include "raycaster.h"


void performRayCasting(double pPosX, double pPosY, double pDirX, double pDirY, double cPlaneX, double cPlaneY, 	std::vector<Uint32> (&texture)[8]){
	std::cout << "MUJI" << std::endl;
	uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	for(int x = 0; x < texWidth; x++)
	for(int y = 0; y < texHeight; y++)
	{
		int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
		//int xcolor = x * 256 / texWidth;
		int ycolor = y * 256 / texHeight;
		int xycolor = y * 128 / texHeight + x * 128 / texWidth;
		texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
		texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
		texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
		texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
		texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
		texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
		texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
		texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
	}
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
		
		int pitch = 100;//idk wtf this does
		// Calculate the start and end of vertical line
		int ystart = SCREEN_HEIGHT / 2 - lineHeight / 2 + pitch;
		if (ystart < 0) ystart = 0;
		int yend = SCREEN_HEIGHT / 2 + lineHeight / 2 + pitch;
		if (yend >= SCREEN_HEIGHT) yend = SCREEN_HEIGHT - 1;
		
		//texturing calculations
		int textNum = worldMap[posRayInMapX][posRayInMapY] - 1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = pPosY + perpWallDist * rayDirY;
		else
			wallX = pPosX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = int(wallX * double(texWidth));
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side ==1 && rayDirY < 0) texX = texWidth - texX -1;
		//How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		//Starting texture coordinate
		double texPos = (ystart - pitch - SCREEN_HEIGHT/2 + lineHeight/2) * step;
		for(int y = ystart; y < yend; y++)
		{
			//cast the texture coordinate to integer, and mask with (texheight -1) in case of overflow
			int texY = (int)texPos & (texHeight -1);
			texPos += step;
			Uint32 color = texture[textNum][texHeight * texY + texX];
			buffer[y][x] = color;
		}
			// uint8_t byte1 = (color >> 16) & 0xFF;
    		// uint8_t byte2 = (color >> 8) & 0xFF;
    		// uint8_t byte3 = color & 0xFF;
		// SDL_Color drawColor = {255, 255, 255, 255};
		// switch (worldMap[posRayInMapX][posRayInMapY]) {
		// 	case 1: 
		// 		drawColor = (SDL_Color){255, 0, 0, 255}; // Red
		// 		break;
		// 	case 2: 
		// 		drawColor = (SDL_Color){0, 255, 0, 255}; // Green
		// 		break;
		// 	case 3: 
		// 		drawColor = (SDL_Color){0, 0, 255, 255}; // Blue
		// 		break;
		// 	case 4: 
		// 		drawColor = (SDL_Color){255, 255, 255, 255}; // White
		// 		break;
		// 	default:
		// 		drawColor = (SDL_Color){128, 0, 128, 255}; // Purple
		// 		break;
		// }

		// if (side == 1)
		// 	drawColor = (SDL_Color){static_cast<Uint8>(drawColor.r / 2),
		// 		static_cast<Uint8>(drawColor.g / 2), 
		// 		static_cast<Uint8>(drawColor.b / 2), 
		// 		static_cast<Uint8>(drawColor.a / 2)
		// 	};

		drawVerLine(x, ystart, yend, buffer);
	}
}
