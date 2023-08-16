#include "sdlGraphics.h"
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

TTF_Font* font;

bool isRunning = true;

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO ) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Failed to initialize SDL2_ttf: %s\n", TTF_GetError());
		return false;
	}

	window = SDL_CreateWindow("CG Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window) {
		fprintf(stderr, "Failed to initialize SDL window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		fprintf(stderr, "Failed to initialize SDL renderer: %s\n", SDL_GetError());
		return false;
	}

	font = TTF_OpenFont("../res/fonts/BeckyTahlia-MP6r.ttf", 18);
	if (font == NULL) 
		fprintf(stderr, "Failed to load font: %s\n", SDL_GetError());

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);

	// Set background color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear the entire screen to our selected color
	render();

	fprintf(stdout, "Game Started\n");
	return true;
}

void destroySDL() {
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

void render() {
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void drawPixel(int x, int y, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void drawText(const char *text, int x, int y, SDL_Color color) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};

	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

	SDL_DestroyTexture(textTexture);
}
