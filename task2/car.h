#pragma once
#include <windows.h>
class Car {
public:
	int xc;
	Car() { xc = 0; };
	void drawCar(HDC &hdc, int cxClient, int cyClient)
	{
		Ellipse(hdc, xc + 20, cyClient - 45, xc + 60, cyClient - 5);
		Ellipse(hdc, xc + 120, cyClient - 45, xc + 160, cyClient - 5);
		Rectangle(hdc, xc, cyClient - 100, xc + 101, cyClient - 25);
		Rectangle(hdc, xc + 100, cyClient - 150, xc + 200, cyClient - 25);
	}
};