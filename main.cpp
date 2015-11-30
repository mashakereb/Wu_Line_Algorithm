
#include "draw.h"

#define PI  3.141592653

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "CG_Example";
struct line {
	int x0, x1, y0, y1;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;  
	MSG lpMsg;
	WNDCLASS wc;
	
	// Fill the window class structure
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon		 = NULL;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szClassName;

	// Registrates the class of window
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}
	
	// Create the main window of the application
	hWnd = CreateWindow ( 
		    szClassName,					                  
            "Vu lines",
            WS_OVERLAPPEDWINDOW,			// window's stile                                            
            50,   50,						// position of window
            600,  600,						// size
            (HWND) NULL,				  
            (HMENU) NULL,					      
            (HINSTANCE)hInstance,
            NULL    );
	
	if (!hWnd) 
	{
		MessageBox(NULL, "Cannot create main window!", "Error", MB_OK);
		return 0;
	}

	// Shows the window
	ShowWindow(hWnd, nCmdShow); 
	UpdateWindow(hWnd);

	// Perform the message loop before closing the application
	while (GetMessage(&lpMsg, NULL, 0, 0))  {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}

	return (lpMsg.wParam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT Rect;
	HDC hdc, hCmpDC;
	HBITMAP hBmp;
	static int x1, y1, x2, y2;
	static int state = 0;
	static bool win_paint = false;

	switch (messg)
	{
		case WM_PAINT:
			GetClientRect(hWnd, &Rect);
			hdc = BeginPaint(hWnd, &ps);
			// Create a new context for double buffering
			hCmpDC = CreateCompatibleDC(hdc);
			hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
				Rect.bottom - Rect.top);
			SelectObject(hCmpDC, hBmp);
			// Shading background color
			LOGBRUSH br;
			br.lbStyle = BS_SOLID;
			br.lbColor = 0xFFFFFF;
			HBRUSH brush;
			brush = CreateBrushIndirect(&br);
			FillRect(hCmpDC, &Rect, brush);
			DeleteObject(brush);

			// Drawing
			SetBkColor(hCmpDC, 0xFFFFFF);
			if (win_paint) {
				TextOut(hCmpDC, 10, 10, "Standart function", 18);
			} else {
				TextOutA(hCmpDC, 10, 10, "My function",12);
			}
			if (state == 1)
			{
				if (win_paint) {
					MoveToEx(hCmpDC, x1, y1, NULL);
					LineTo(hCmpDC, x2, y2);
				}
				else drawWuLine(hCmpDC, x1, y1, x2, y2);
			}
			
			// Displaying
			SetStretchBltMode(hdc, COLORONCOLOR);
			BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
				hCmpDC, 0, 0, SRCCOPY);
			DeleteDC(hCmpDC);
			DeleteObject(hBmp);
			hCmpDC = NULL;
			EndPaint(hWnd, &ps);
			break;

		case WM_LBUTTONDOWN:
			int x, y;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			state++;
			if (state == 3) {
				state = 1;
			}
			if (state == 1) {
				x1 = x;
				y1 = y;
				x2 = x;
				y2 = y;
			}
			break;

		case WM_MOUSEMOVE:
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			if (state == 1){
				x2 = x;
				y2 = y;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			
			break;

		case WM_LBUTTONUP: 
			break;

		case WM_KEYDOWN:
			win_paint = !win_paint;
			InvalidateRect(hWnd, NULL, FALSE);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, messg, wParam, lParam));
	}

	return (0);
}
