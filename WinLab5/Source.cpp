#undef UNICODE
#include "windows.h"
#define IDM_MYMENURESOURCE   3

using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LPCSTR szClassName = "WinAPI";
LPCSTR szTitle = "Windows application";
const UINT_PTR redTimer = 0, greenTimer = 2, yellowTimer = 1;
bool redOn = false, greenOn = false, yellowOn = false;
int greenRad = 100, redRad = 80, yellowRad = 130;
int time = 0;
const UINT RedMenu = 100, YellowMenu = 101, GreenMenu = 102;
COLORREF color;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	if (!hPrevInstance)
	{
		if (!InitApplication(hInstance))
			return (FALSE);
	}
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE - 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDM_MYMENURESOURCE);
	wc.lpszClassName = szClassName;
	return RegisterClass(&wc);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(
		szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)    return (FALSE);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static HMENU menu, menu1;
	static HDC hdc;
	static HBRUSH red;
	static HBRUSH yellow;
	static HBRUSH green;
	int cxClient, cyClient;

	switch (message)
	{
	case WM_CREATE:
	{
		red = CreateSolidBrush(RGB(255, 0, 0));
		yellow = CreateSolidBrush(RGB(255, 255, 0));
		green = CreateSolidBrush(RGB(0, 255, 0));
		SetTimer(hwnd, redTimer, 1000, (TIMERPROC)NULL);
		SetTimer(hwnd, greenTimer, 500, (TIMERPROC)NULL);
		SetTimer(hwnd, yellowTimer, 300, (TIMERPROC)NULL);
		/*
		menu = CreateMenu();
		menu1 = CreateMenu();
		AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)menu1, "File");
		AppendMenu(menu1, MF_STRING, 100, "Red Light");
		AppendMenu(menu1, MF_STRING, 101, "Yellow Light");
		AppendMenu(menu1, MF_STRING, 102, "Green Light");
		SetMenu(hwnd, menu);
		SetMenu(hwnd, menu1);
		*/
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		/*
		case RedMenu:
			redOn = redOn ^ 1;
			break;
		case GreenMenu:
			greenOn = greenOn ^ 1;
			break;
		case YellowMenu:
			yellowOn = yellowOn ^ 1;
			break;
			*/
		case IDM_FI_OPEN:
			DoFileOpen();	// определяется программой
			break;
		case IDM_FI_CLOSE:
			DoFileClose();	// определяется программой
			break;
		break;
		}
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		RECT rect;
		GetClientRect(hwnd, &rect);
		cxClient = rect.right;
		cyClient = rect.bottom;
		FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		SelectObject(hdc, green);
		Ellipse(hdc, cxClient / 4 - greenRad, cyClient / 4 - greenRad, cxClient / 4 + greenRad, cyClient / 4 + greenRad);
		SelectObject(hdc, red);
		Ellipse(hdc, cxClient * 3 / 4 - redRad, cyClient / 4 - redRad, cxClient * 3 / 4 + redRad, cyClient / 4 + redRad);
		SelectObject(hdc, yellow);
		Ellipse(hdc, cxClient * 3 / 4 - yellowRad, cyClient * 3 / 4 - yellowRad, cxClient * 3 / 4 + yellowRad,
			cyClient * 3 / 4 + yellowRad);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_TIMER:
	{
		switch (wParam)
		{
		case yellowTimer:
			if (yellowOn)
				if (yellowRad == 130)
					yellowRad = 20;
				else yellowRad = 130;
			else yellowRad = 130;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case redTimer:
			if (redOn)
				if (redRad == 80)
					redRad = 20;
				else redRad = 80;
			else redRad = 80;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case greenTimer:
			if (greenOn)
				if (greenRad == 100)
					greenRad = 20;
				else greenRad = 100;
			else greenRad = 100;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		color = GetPixel(GetDC(hwnd), (int)LOWORD(lParam), (int)HIWORD(lParam));
		if (color == RGB(255, 0, 0))
			redOn = true;
		if (color == RGB(255, 255, 0))
			yellowOn = true;
		if (color == RGB(0, 255, 0))
			greenOn = true;
		break;
	}
	case WM_RBUTTONDOWN:
		color = GetPixel(GetDC(hwnd), (int)LOWORD(lParam), (int)HIWORD(lParam));
		if (color == RGB(255, 0, 0))
			redOn = false;
		if (color == RGB(255, 255, 0))
			yellowOn = false;
		if (color == RGB(0, 255, 0))
			greenOn = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
