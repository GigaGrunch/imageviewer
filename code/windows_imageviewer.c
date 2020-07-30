#pragma warning(push, 0)
#include "windows.h"
#include "../../SDL/include/SDL.h"
#include <stdbool.h>
#pragma warning(pop)

typedef enum
{
	Error_mmap,

	Error_SDL_Init,
	Error_SDL_CreateWindow,
	Error_SDL_CreateRenderer,
	Error_SDL_CreateTexture,
	Error_SDL_WaitEvent,
	Error_SDL_RenderCopy,
	Error_SDL_UpdateTexture,
} Error;

int CALLBACK WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       lpCmdLine,
    int         nCmdShow)
{
	printf("hello world!\n");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return Error_SDL_Init;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Image Viewer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024, 768,
		SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		return Error_SDL_CreateWindow;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		return Error_SDL_CreateRenderer;
	}

	bool app_running = true;
	while (app_running)
	{
		SDL_Event event[1] = {0};
		if (SDL_WaitEvent(event) == 0)
		{
			return Error_SDL_WaitEvent;
		}

		if (event->type == SDL_WINDOWEVENT)
		{
			if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			{
				printf("window event: SDL_WINDOWEVENT_CLOSE\n");
				app_running = false;
			}
		}
	}

	printf("bye bye\n");
	return 0;
}