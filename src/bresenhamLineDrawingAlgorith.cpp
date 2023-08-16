#include "bresenhamLineDrawingAlgorith.h"

void drawVerLine(int xstart, int ystart, int yend, SDL_Color color) {
	int labelx = 0, labely = 0;
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

	drawPixel(x, y, color);

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
			drawPixel(x, y, color);
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
			drawPixel(x, y, color);
		}
	}
}
