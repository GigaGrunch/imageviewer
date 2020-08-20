#pragma warning(push, 0)
#include <stdio.h>
#include <windows.h>
#pragma warning(pop)

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	printf("ImageViewer for Windows (native) says 'hello!'\n");

	WNDCLASS window_class = {0};
	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = hInstance;
	window_class.lpszClassName = "Image Viewer Window Class";
	RegisterClass(&window_class);

	HWND window = CreateWindowEx(
		0,                              // Optional window styles.
		"Image Viewer Window Class",                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (NULL == window)
	{
		return 0;
	}

	ShowWindow(window, nCmdShow);

	printf("ImageViewer for Windows (native) says 'bye bye'\n");
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SIZE:
		{
			int width = LOWORD(lParam);  // Macro to get the low-order word.
			int height = HIWORD(lParam); // Macro to get the high-order word.

			// Respond to the message:
			// OnSize(hwnd, (UINT)wParam, width, height);
			break;
		}
	}
}
