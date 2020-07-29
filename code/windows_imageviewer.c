#include "windows.h"
#include "../../SDL/include/SDL.h"

int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow
    )
{
	SDL_Log("hello world!");
}