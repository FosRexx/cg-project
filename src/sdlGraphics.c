#include "sdlGraphics.h"

SDL_Window* window = NULL;
SDL_GLContext* openGLContext = NULL;

bool isRunning = true;

bool initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO ) != 0)
	{
		fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("CG Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (!window) {
		fprintf(stderr, "Failed to initialize SDL window: %s\n", SDL_GetError());
		return false;
	}

	openGLContext = SDL_GL_CreateContext(window);
	if (!openGLContext) {
		fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
		return false;
	}

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		fprintf(stderr, "Failed to initialize glad: %s\n", SDL_GetError());
		return false;
	}

	/* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); */
	/* if (!renderer) { */
	/* 	fprintf(stderr, "Failed to initialize SDL renderer: %s\n", SDL_GetError()); */
	/* 	return false; */
	/* } */

	/* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 18); */
	/* if (font == NULL) */ 
	/* 	fprintf(stderr, "Failed to load font: %s\n", SDL_GetError()); */

	/* SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT); */
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	/* SDL_SetRelativeMouseMode(SDL_TRUE); */
	/* SDL_ShowCursor(SDL_DISABLE); */

	/* // Set background color to black */
	/* SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear the entire screen to our selected color
	render();

	fprintf(stdout, "Game Started\n");
	return true;
}

void destroySDL() {
	SDL_GL_DeleteContext(window);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void render() {
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawPixel(int x, int y, SDL_Color color) {
	glBegin(GL_POINTS);
	glCOlor3f(color.r, color.g, color.b);
	glVertex2f(x, y);
	/* SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); */
	/* SDL_RenderDrawPoint(renderer, x, y); */
	/* SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); */
}

/* void drawText(const char *text, int x, int y, SDL_Color color) { */
/* 	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color); */

/* 	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); */
/* 	SDL_Rect destRect = {x, y, textSurface->w, textSurface->h}; */

/* 	SDL_FreeSurface(textSurface); */

/* 	SDL_RenderCopy(renderer, textTexture, NULL, &destRect); */

/* 	SDL_DestroyTexture(textTexture); */
/* } */
