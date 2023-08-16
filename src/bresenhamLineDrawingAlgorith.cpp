#include "bresenhamLineDrawingAlgorith.h"

void drawVerLine(int xstart, int ystart, int yend, uint32_t buffer[][SCREEN_WIDTH]){
	int labelx = 0, labely = 0;
	uint32_t color;
	float delx = 0, dely = 0;
	float p, x, y;

	delx = 0;
	dely = abs(yend - ystart);

	/* if (xstart > xstart) */ 
	/* 	labelx = 1; */
	/* else */
	/* 	labelx = -1; */
	labelx = -1;

	if (yend > ystart) 
		labely = 1;
	else
		labely = -1;

	x = xstart, y = ystart;

	if (delx > dely) {
		p = 2 * dely - delx;
		for (int i = 1; i <= delx; i++) {
			if (p < 0) {
				x = x + labelx;
				/* y = y; */
				p = p + 2 * dely;
			} else {
				x = x + labelx;
				y = y + labely;
				p = p + 2 * dely - 2 * delx;
			}
			//i dont know wtf i just did 
			color = buffer[ystart][xstart];
			uint8_t byte1 = (color >> 16) & 0xFF;
    		uint8_t byte2 = (color >> 8) & 0xFF;
    		uint8_t byte3 = color & 0xFF;
			SDL_Color Scolor = {byte1, byte2, byte3, 255};
			drawPixel(x, y, Scolor);
			ystart += 1;
		}
	} else {
		p = 2 * delx - dely;
		for (int i = 1; i <= dely; i++) {
			if (p < 0) {
				/* x = x; */
				y = y + labely;
				p = p + 2 * delx;
			} else {
				x = x + labelx;
				y = y + labely;
				p = p + 2 * delx - 2 * dely;
			}
			color = buffer[xstart][ystart];
			uint8_t byte1 = (color >> 16) & 0xFF;
    		uint8_t byte2 = (color >> 8) & 0xFF;
    		uint8_t byte3 = color & 0xFF;
			SDL_Color Scolor = {byte1, byte2, byte3, 255};
			drawPixel(x, y, Scolor);
			ystart += 1;
		}
	}
	for(int x = 0; x < 720; x++)
	{
		for(int y = 0; y < 1280; y++){
			buffer[x][y] = 0;
		}
	}
}
