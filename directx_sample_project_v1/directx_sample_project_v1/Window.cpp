#include "Window.h"

Window::Window(int width, int height, const char* name)
	:
	width(width),
	height(height),
	hInstance(GetModuleHandle(nullptr))
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = windowName;

	RegisterClass(&wc);

	RECT winRect;
	winRect.left = 100;
	winRect.right = width + winRect.left;
	winRect.top = 100;
	winRect.bottom = height + winRect.top;
	AdjustWindowRect(&winRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		windowName, 
		name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		winRect.right - winRect.left, 
		winRect.bottom - winRect.top,
		nullptr,
		nullptr,
		hInstance,
		this
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	UnregisterClass(windowName, hInstance);
	DestroyWindow(hWnd);
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return msg.wParam;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

void onSize(HWND hwnd, UINT flag, int width, int height)
{

}

LRESULT __stdcall Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int heigt = HIWORD(lParam);
			onSize(hWnd, (UINT)wParam, width, heigt);
			return 0;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// All painting occurs here, between BeginPaint and EndPaint.
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_CLOSE:
			if (MessageBox(hWnd, "Really quit?", "My application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hWnd);
			}
			// Else: User canceled. Do nothing.
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

