#pragma once

#include "resource.h"
#include "car.h"
const UINT_PTR TIMER = 0;
static HPEN pen;

static void Paint(HWND hWnd, LPPAINTSTRUCT lpPS, Car &car)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;

	GetClientRect(hWnd, &rc);
	hdcMem = CreateCompatibleDC(lpPS->hdc);
	hbmMem = CreateCompatibleBitmap(lpPS->hdc,
		rc.right - rc.left,
		rc.bottom - rc.top);

	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
	SelectObject(hdcMem, pen);

	FillRect(hdcMem, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	if (car.xc >= rc.right - rc.left)
		car.xc = -200;
	car.drawCar(hdcMem, rc.right - rc.left, rc.bottom - rc.top);

	BitBlt(lpPS->hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);
}