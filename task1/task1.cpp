// task1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "task1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
const UINT_PTR redTimer = 0, greenTimer = 2, yellowTimer = 1;
bool redOn = false, greenOn = false, yellowOn = false;
int greenRad = 100, redRad = 80, yellowRad = 130;
int time = 0;
COLORREF color;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TASK1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TASK1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static PAINTSTRUCT ps;
	static HDC hdc;
	static HBRUSH red;
	static HBRUSH yellow;
	static HBRUSH green;
	int cxClient, cyClient;
	static HMENU menu;
	static HINSTANCE hInstance;
	static POINT point;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hwnd);
                break;
			case ID_FILE_GREENBUTTON:
				greenOn = greenOn ^ 1;
				break;
			case ID_FILE_YELLOWBUTTON:
				yellowOn = yellowOn ^ 1;
				break;
			case ID_FILE_REDBUTTON:
				redOn = redOn ^ 1;
				break;
			case ID_GREENBUTTON_GREENBUTTON:
				greenOn = greenOn ^ 1;
				break;
            default:
                return DefWindowProc(hwnd, message, wParam, lParam);
            }
			InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
	case WM_CREATE:
	{
		red = CreateSolidBrush(RGB(255, 0, 0));
		yellow = CreateSolidBrush(RGB(255, 255, 0));
		green = CreateSolidBrush(RGB(0, 255, 0));
		SetTimer(hwnd, redTimer, 1000, (TIMERPROC)NULL);
		SetTimer(hwnd, greenTimer, 500, (TIMERPROC)NULL);
		SetTimer(hwnd, yellowTimer, 300, (TIMERPROC)NULL);
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		menu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
		menu = GetSubMenu(menu, 0);
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
		break;
	}
	case WM_RBUTTONDOWN:
		color = GetPixel(GetDC(hwnd), (int)LOWORD(lParam), (int)HIWORD(lParam));
		if (color == RGB(255, 0, 0))
			redOn = false;
		if (color == RGB(255, 255, 0))
			yellowOn = false;
		if (color == RGB(0, 255, 0))
		{
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ClientToScreen(hwnd, &point);
			TrackPopupMenuEx(menu, MF_POPUP, point.x, point.y, hwnd, NULL);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
