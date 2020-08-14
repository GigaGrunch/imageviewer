#include "imageviewer.h"

int width = 1024;
int height = 768;

int imageviewer_main(void)
{
	printf("now entering platform independent land\n");

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		return Error_SDL_Init;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Image Viewer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_RESIZABLE);
	if (NULL == window)
	{
		return Error_SDL_CreateWindow;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (NULL == renderer)
	{
		return Error_SDL_CreateRenderer;
	}

	Pixel* pixels = malloc(width * height * sizeof(Pixel));
	if (NULL == pixels)
	{
		return Error_malloc;
	}

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

	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		width, height);
	if (NULL == texture)
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
		if (0 == SDL_WaitEvent(event))
		{
			return Error_SDL_WaitEvent;
		}

		if (SDL_WINDOWEVENT == event->type)
		{
			if (SDL_WINDOWEVENT_CLOSE == event->window.event)
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

	return 0;
}
