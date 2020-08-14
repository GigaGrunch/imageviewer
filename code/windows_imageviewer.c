#pragma warning(push, 0)
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "../../SDL/include/SDL.h"
#include "windows.h"
#pragma warning(pop)

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

int width = 1024;
int height = 786;
int pixelSize = 4;

typedef struct
{
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Pixel;

int WinMain(void)
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

	Pixel* pixels = malloc(width * height * sizeof(Pixel));

	{
		Pixel* currentPixel = pixels;
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (y < (height / 3))
				{
					currentPixel->r = 255;
					currentPixel->g = 0;
					currentPixel->b = 0;
				}
				else if (y < (2 * height / 3))
				{
					currentPixel->r = 0;
					currentPixel->g = 255;
					currentPixel->b = 0;
				}
				else
				{
					currentPixel->r = 0;
					currentPixel->g = 0;
					currentPixel->b = 255;
				}
				
				currentPixel->a = 255;
				++currentPixel;
			}
		}
	}

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	if (texture == NULL)
	{
		return Error_SDL_CreateTexture;
	}

	if (0 != SDL_UpdateTexture(
		texture,
		NULL, // rect
		pixels,
		width * sizeof(Pixel))) // pitch
	{
		return Error_SDL_UpdateTexture;
	}

	SDL_Rect renderRect[1] = {0};
	renderRect->w = width;
	renderRect->h = height;

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

		if (0 != SDL_RenderCopy(
			renderer,
			texture,
			renderRect, // srcrect
			renderRect)) // dstrect
		{
			return Error_SDL_RenderCopy;
		}

		SDL_RenderPresent(renderer);
	}

	printf("bye bye\n");
	return 0;
}