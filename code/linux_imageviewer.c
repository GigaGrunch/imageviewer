#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <sys/mman.h>

typedef uint8_t u8;

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

typedef struct
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Pixel;

int width = 1024;
int height = 768;

int main(void)
{
	SDL_Log("hello world!");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return Error_SDL_Init;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Image Viewer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
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

	void* memory = mmap(
		NULL,
		width * height * sizeof(Pixel),
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1,
		0);
	if (memory == (void*)(-1))
	{
		return Error_mmap;
	}


	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STATIC,
		width, height);
	if (texture == NULL)
	{
		return Error_SDL_CreateTexture;
	}

	if (SDL_UpdateTexture(
		texture,
		NULL,
		memory,
		width * sizeof(Pixel)) != 0)
	{
		return Error_SDL_UpdateTexture;
	}

	bool app_running = true;
	while (app_running)
	{
		SDL_Event event = {};
		if (SDL_WaitEvent(&event) == 0)
		{
			return Error_SDL_WaitEvent;
		}

		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_Log("window event: SDL_WINDOWEVENT_CLOSE");
				app_running = false;
			}
		}

		if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0)
		{
			return Error_SDL_RenderCopy;
		}

		SDL_RenderPresent(renderer);
	}

	SDL_Log("bye bye");
	return 0;
}