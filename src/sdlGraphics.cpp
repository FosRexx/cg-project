#include "sdlGraphics.h"

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

	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		std::cout << "IMG_Init: Failed to init required jpg and png support!" << std::endl;
		std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
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

//Draws a buffer of pixels to the screen
void drawBuffer(uint32_t* buffer) {
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_PIXELFORMAT_RGB888);
	if (!surface) {
		fprintf(stderr, "Failed to create SDL Surface: %s\n", SDL_GetError());
		return;
	}

	uint32_t* bufp = (uint32_t*)surface->pixels;

	for(int y = 0; y < SCREEN_HEIGHT; y++)
	{
		for(int x = 0; x < SCREEN_WIDTH; x++)
		{
			*bufp = buffer[y * SCREEN_WIDTH + x];
			bufp++;
		}
		bufp = (uint32_t*)((Uint8*)bufp + surface->pitch - SCREEN_WIDTH * sizeof(uint32_t));}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_FreeSurface(surface);
		fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
		return;
	}

	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void drawText(const char *text, int x, int y, SDL_Color color) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect destRect = {x, y, textSurface->w, textSurface->h};

	SDL_FreeSurface(textSurface);

	SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

	SDL_DestroyTexture(textTexture);
}

// Function to load an image into a vector<int> (texture)
void loadTextureData(std::vector<uint32_t>& texture, const char* imagePath) {
	SDL_Surface* surface = IMG_Load(imagePath);
	if (!surface) {
		fprintf(stderr, "Failed to create surface: %s\n", SDL_GetError());
		return;
	}

	// Assuming that texture dimensions are texWidth and texHeight
	int texWidth = surface->w;
	int texHeight = surface->h;

	// Assuming that the texture vector is already resized to texWidth * texHeight
	Uint32* pixels = static_cast<Uint32*>(surface->pixels);
	for (int i = 0; i < texWidth * texHeight; i++) {
		Uint8 r, g, b, a;
		SDL_GetRGBA(pixels[i], surface->format, &r, &g, &b, &a);

		// Combine the color channels into a single integer
		uint32_t color = 0x1000000 * r + 0x10000 * g + 0x100 * b + a;

		texture[i] = color;
	}

	SDL_FreeSurface(surface);
}
