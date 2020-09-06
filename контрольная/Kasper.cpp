#include <iostream>
#include <windows.h>

#include <wchar.h>

#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void DrawPixels(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PWSTR lpCmdLine,int nCmdShow) {

	MSG msg;

	WNDCLASSW wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW;

	wc.lpszClassName = L"Pixels";

	wc.hInstance = hInstance;

	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

	wc.lpfnWndProc = WndProc;

	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);

	CreateWindowW(wc.lpszClassName, L"Pixels",

		WS_OVERLAPPEDWINDOW | WS_VISIBLE,

		100, 100, 300, 250, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	srand(time(NULL));

	return (int)msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,

	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_PAINT:

		DrawPixels(hwnd);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;

	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);

}

void DrawPixels(HWND hwnd) {

	PAINTSTRUCT ps;

	RECT r;

	GetClientRect(hwnd, &r);

	if (r.bottom == 0) {

		return;

	}
	HDC hdc = BeginPaint(hwnd, &ps);
	Rectangle(hdc, 0, 0, 200, 200);
	Ellipse(hdc, 100, 105, 180, 195);
	for (int i = 0; i < 100; i++)
	{
		for (int f = 0; f < 200; f++)
		{
			COLORREF top = GetPixel(hdc, f, i);
			COLORREF bottom = GetPixel(hdc, f, 101 + i);
			SetPixel(hdc, f, i, bottom);
			SetPixel(hdc, f, (101+i), top);
		}
	}
	EndPaint(hwnd, &ps);

}