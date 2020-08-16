#include "imageviewer.h"

int width = 1024;
int height = 768;

void create_some_pattern(Pixel* pixels);
SDL_Rect match_preserve_ratio(SDL_Rect rect_to_match, SDL_Rect max_rect);

void imageviewer_main(void)
{
	printf("now entering platform independent land\n");

	SDL_Window* window = SDL_CreateWindow(
		"Image Viewer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_RESIZABLE);
	if (NULL == window)
	{
		exit(Error_SDL_CreateWindow);
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (NULL == renderer)
	{
		exit(Error_SDL_CreateRenderer);
	}

	Pixel* pixels = malloc(width * height * sizeof(Pixel));
	if (NULL == pixels)
	{
		exit(Error_malloc);
	}

	create_some_pattern(pixels);

	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STATIC,
		width, height);
	if (NULL == texture)
	{
		exit(Error_SDL_CreateTexture);
	}

	if (0 != SDL_UpdateTexture(
		texture,
		NULL, // rect
		pixels,
		width * sizeof(Pixel))) // pitch
	{
		exit(Error_SDL_UpdateTexture);
	}

	SDL_Rect source_rect = {0};
	source_rect.w = width;
	source_rect.h = height;

	SDL_Rect window_rect = {0};
	window_rect.w = width;
	window_rect.h = height;

	bool app_running = true;
	while (app_running)
	{
		SDL_Event event[1] = {0};
		if (0 == SDL_WaitEvent(event))
		{
			exit(Error_SDL_WaitEvent);
		}

		if (SDL_WINDOWEVENT == event->type)
		{
			switch (event->window.event)
			{
				case SDL_WINDOWEVENT_CLOSE:
				{
					printf("window event: SDL_WINDOWEVENT_CLOSE\n");
					app_running = false;
					break;
				}
				case SDL_WINDOWEVENT_RESIZED:
				{
					window_rect.w = event->window.data1;
					window_rect.h = event->window.data2;
					break;
				}
			}
		}

		SDL_Rect dest_rect = match_preserve_ratio(source_rect, window_rect);

		if (0 != SDL_RenderCopy(
			renderer,
			texture,
			&source_rect, // srcrect
			&dest_rect)) // dstrect
		{
			exit(Error_SDL_RenderCopy);
		}

		SDL_RenderPresent(renderer);
	}
}

SDL_Rect match_preserve_ratio(SDL_Rect rect_to_match, SDL_Rect max_rect)
{
	SDL_Rect matching_rect = {0};

	float ratio_to_preserve = (float) rect_to_match.w / rect_to_match.h;
	float given_ratio = (float) max_rect.w / max_rect.h;
	bool rect_to_match_is_wider = ratio_to_preserve > given_ratio;

	if (rect_to_match_is_wider)
	{
		matching_rect.w = max_rect.w;
		matching_rect.h = max_rect.w / ratio_to_preserve;
	}
	else
	{
		matching_rect.h = max_rect.h;
		matching_rect.w = max_rect.h * ratio_to_preserve;
	}

	return matching_rect;
}

void create_some_pattern(Pixel* pixels)
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
