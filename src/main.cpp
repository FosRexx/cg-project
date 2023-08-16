#include <iostream>
#include <math.h>

#include "sdlGraphics.h"
#include "raycaster.h"
#include "worldMap.h"


int main(int argc, char **argv) {
	(void) argc;
	(void) argv;

	// Position of player
	double pPosX = 12, pPosY = 12;
	// Direction the player is looking in
	double pDirX = -1, pDirY = 0;
	// Vector of camera plane
	double cPlaneX = 0, cPlaneY = 0.66;

	double currentTime = 0;
	double previousTime = 0;
	double deltaTime = 0;

	bool isSDLInit = initSDL();

	generateTextures();

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	previousTime = SDL_GetTicks();
	while (isSDLInit && isRunning) {
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0;
		previousTime = SDL_GetTicks();

		double velocity = 5 * deltaTime; // Pixels/second

		double tempRotatedDirX = 0, tempRotatedDirY = 0;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_MOUSEMOTION:
					{
						int mouseMoveX = -event.motion.xrel;
						
						double rotationSpeed = mouseMoveX * deltaTime * 0.1;

						double oldDirX = pDirX;
						pDirX = pDirX * cos(rotationSpeed) - pDirY * sin(rotationSpeed);
						pDirY = oldDirX * sin(rotationSpeed) + pDirY * cos(rotationSpeed);

						double oldPlaneX = cPlaneX;
						cPlaneX = cPlaneX * cos(rotationSpeed) - cPlaneY * sin(rotationSpeed);
						cPlaneY = oldPlaneX * sin(rotationSpeed) + cPlaneY * cos(rotationSpeed);
					}
					break;
			}
		}

		// Movement
		if (keyboardState[SDL_SCANCODE_W]) {
			if (worldMap[(int)(pPosX + pDirX * velocity)][(int)pPosY] == 0) pPosX += pDirX * velocity;
			if (worldMap[(int)pPosX][(int)(pPosY + pDirY * velocity)] == 0) pPosY += pDirY * velocity;
		}

		if (keyboardState[SDL_SCANCODE_A]) {
			tempRotatedDirX = pDirX * cos(1.570796) - pDirY * sin(1.570796);
			tempRotatedDirY = pDirX * sin(1.570796) + pDirY * cos(1.570796);

			if (worldMap[(int)(pPosX + tempRotatedDirX * velocity)][(int)pPosY] == 0) pPosX += tempRotatedDirX * velocity;
			if (worldMap[(int)pPosX][(int)(pPosY + tempRotatedDirY * velocity)] == 0) pPosY += tempRotatedDirY * velocity;
		}

		if (keyboardState[SDL_SCANCODE_S]) {
			if (worldMap[(int)(pPosX - pDirX * velocity)][(int)pPosY] == 0) pPosX -= pDirX * velocity;
			if (worldMap[(int)pPosX][(int)(pPosY - pDirY * velocity)] == 0) pPosY -= pDirY * velocity;
		}

		if (keyboardState[SDL_SCANCODE_D]) {
			tempRotatedDirX = pDirX * cos(-1.570796) - pDirY * sin(-1.570796);
			tempRotatedDirY = pDirX * sin(-1.570796) + pDirY * cos(-1.570796);

			if (worldMap[(int)(pPosX + tempRotatedDirX * velocity)][(int)pPosY] == 0) pPosX += tempRotatedDirX * velocity;
			if (worldMap[(int)pPosX][(int)(pPosY + tempRotatedDirY * velocity)] == 0) pPosY += tempRotatedDirY * velocity;
		}

		performRayCasting(pPosX, pPosY, pDirX, pDirY, cPlaneX, cPlaneY);

		drawBuffer(buffer[0]);
		/* for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) buffer[y][x] = 0; //clear the buffer */


		char dTime[sizeof(deltaTime)];
		snprintf(dTime, sizeof(dTime), "%.2f", 1 / deltaTime);
		drawText(dTime, 0, 0, (SDL_Color){255, 255, 255, 255});

		render();
	}
	destroySDL();
	return 0;
}
