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

	previousTime = SDL_GetTicks();
	while (isSDLInit && isRunning) {
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0;
		previousTime = SDL_GetTicks();

		double velocity = 5 * deltaTime; // Pixels/second
		double angularVelocity = 3 * deltaTime; // Radians/second

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_w:
							if (worldMap[(int)(pPosX + pDirX * velocity)][(int)pPosY] == 0) pPosX += pDirX * velocity;
							if (worldMap[(int)pPosX][(int)(pPosY + pDirY * velocity)] == 0) pPosY += pDirY * velocity;
							break;

						case SDLK_a:
							break;

						case SDLK_s:
							if (worldMap[(int)(pPosX - pDirX * velocity)][(int)pPosY] == 0) pPosX -= pDirX * velocity;
							if (worldMap[(int)pPosX][(int)(pPosY - pDirY * velocity)] == 0) pPosY -= pDirY * velocity;
							break;

						case SDLK_d:
							break;

					}
					break;
			}
		}

		performRayCasting(pPosX, pPosY, pDirX, pDirY, cPlaneX, cPlaneY);

		char dTime[sizeof(deltaTime)];
		snprintf(dTime, sizeof(deltaTime), "%lf", 1 / deltaTime);

		drawText(dTime, 0, 0, (SDL_Color){255, 255, 255, 255});

		render();

	}
	destroySDL();
	return 0;
}
