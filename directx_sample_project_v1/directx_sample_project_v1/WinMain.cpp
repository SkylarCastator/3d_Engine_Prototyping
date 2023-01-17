#include "Window.h"

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow
)
{
	Window window(1280, 720, "Basic DirectX Turtoial");

	while (true)
	{
		if (const auto msgCode = Window::ProcessMessages())
			return *msgCode;
	}
}