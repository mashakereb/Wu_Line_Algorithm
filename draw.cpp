#include"draw.h"

inline void swap(int &a, int &b)
{
	int t;
	t = a;
	a = b;
	b = t;
}

void drawWuLine(HDC hdc, int x0, int y0, int x1, int y1)
{
	float alpha;
	int color = 100; 

	//The calculation of the coordinates
	int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
	int dy = (x1 > x0) ? (y1 - y0) : (y0 - y1);

	//If the line is parallel to one of the axis, draw an usual line - fill all the pixels in a row
	if (dx == 0) {
		if (y1 < y0)
		{
			swap(x0, x1);
			swap(y0, y1);
		}
		for (int i = y0; i <= y1; i++) {
			SetPixel(hdc, x1, i, color);
		}
		return;
	}
	if (dy == 0) {

		if (x1 < x0)
		{
			swap(x0, x1);
			swap(y0, y1);
		}
		for (int i = x0; i <= x1; i++) {
			SetPixel(hdc, i, y0, color);
		}
		return;
	}

	//For the X-line (slope coefficient < 1)
	if (abs(dy) < dx)
	{
		//The first point must have a smaller x coordinate
		if (x1 < x0)
		{
			swap(x0, x1);
			swap(y0, y1);
		}
		

		fixed grad = fracToFixed(dy, dx);
		fixed intery = intToFixed(y0) + grad;

		//First point
		SetPixel(hdc, x0, y0, color);

		for (int x = x0 + 1; x < x1; x++)
		{
			alpha = (fractionalPart(intery));
			
			SetPixel(hdc, x, fixedToInt(intery) , RGB(255*alpha, 255 * alpha, 255 * alpha));
			
			SetPixel(hdc, x, fixedToInt(intery) +1, (RGB(255 *(1- alpha), 255 * (1 - alpha), 255 * (1 - alpha) )));
			intery += grad;
		}
		//Last point
		SetPixel(hdc, x1, y1, color);
	}
	//For the Y-line (slope coefficient > 1)
	else
	{
		if (y1 < y0){
			swap(x0, x1);
			swap(y0, y1);
		}
		
		fixed grad = fracToFixed(dx , dy);
		
		fixed interx = intToFixed(x0) + grad;
		
		SetPixel(hdc, x0, y0, color);

		for (int y = y0 + 1; y < y1; y++){
			alpha = (fractionalPart(interx));

			SetPixel(hdc, fixedToInt(interx), y,  RGB(255 * alpha, 255 * alpha, 255 * alpha));

			SetPixel(hdc,  fixedToInt(interx) + 1, y,  (RGB(255 * (1 - alpha), 255 * (1 - alpha), 255 * (1 - alpha))));
			interx += grad;

			
		}
		SetPixel(hdc, x1, y1, color);
	}
}
