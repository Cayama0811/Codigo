#include <windows.h>
#include "main.h"

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {
	// Register the window class
	const wchar_t *CLASS_NAME = L"myWin32WindowClass";
	WNDCLASS wc{};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	// Create the window
	CreateWindow(CLASS_NAME, L"3dGraphics",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,			// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,				// Window initial position
		WIDTH, HEIGHT,						// Window size
		nullptr, nullptr, nullptr, nullptr);
	
	// Window loop
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		Render(hdc);

		EndPaint(hwnd, &ps);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}

void Render(HDC hdc) 
{
	for (auto& vertex : CubeArray)
	{
		DrawPixel(hdc, vertex[0], vertex[1], vertex[2], 8, RGB(255, 0, 0));
	}

	for (auto& edge : CubeEdges)
	{
		int v1 = edge[0];
		int v2 = edge[1];

		DrawLine(
			hdc,

			CubeArray[v1][0], // x1
			CubeArray[v2][0], // x2

			CubeArray[v1][1], // y1
			CubeArray[v2][1], // y2

			CubeArray[v1][2], // z1
			CubeArray[v2][2], // z2

			RGB(0, 0, 255)
		);
	}
}

void DrawPixel(HDC hdc, int x, int y, int z, int size, COLORREF color) 
{
	float screenX = (x * focal) / z;
	float screenY = (y * focal) / z;

	screenX += WIDTH / 2;
	screenY += HEIGHT / 2;

	for (int px = 0; px < size; px++)
	{
		for (int py = 0; py < size; py++)
		{
			SetPixel(
				hdc,
				(int)screenX + px,
				(int)screenY + py,
				color);
		}
	}
}

void DrawLine(HDC hdc, int x1, int x2, int y1, int y2, int z1, int z2,
	COLORREF color)
{
	if (z1 == 0 || z2 == 0) return;

	int sx1 = ((x1 * focal) / z1) + (WIDTH / 2);
	int sy1 = ((y1 * focal) / z1) + (HEIGHT / 2);

	int sx2 = ((x2 * focal) / z2) + (WIDTH / 2);
	int sy2 = ((y2 * focal) / z2) + (HEIGHT / 2);

	int dx = abs(sx2 - sx1);
	int dy = abs(sy2 - sy1);
	
	int sx = (sx1 < sx2) ? 1 : -1;
	int sy = (sy1 < sy2) ? 1 : -1;
	
	int err = dx - dy;

	while (true) 
	{
		SetPixel(hdc, sx1, sy1, color);

		if (sx1 == sx2 && sy1 == sy2) break;

		int e2 = 2 * err;
		
		if (e2 > -dy) 
		{
			err -= dy;
			sx1 += sx;
		}
		if (e2 < dx) 
		{
			err += dx;
			sy1 += sy;
		}
	}
}
