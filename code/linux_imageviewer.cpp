#include <SDL2/SDL.h>
#include <sys/mman.h>

namespace Error
{
	constexpr int SDL_Init = 1;
	constexpr int SDL_CreateWindow = 2;
	constexpr int SDL_CreateRenderer = 3;
	constexpr int mmap = 4;
	constexpr int SDL_CreateTexture = 5;
	constexpr int SDL_WaitEvent = 6;
	constexpr int SDL_RenderCopy = 7;
	constexpr int SDL_UpdateTexture = 8;
}

int main()
{
	SDL_Log("hello world!");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return Error::SDL_Init;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Image Viewer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1024, 768,
		SDL_WINDOW_RESIZABLE);
	if (window == nullptr)
	{
		return Error::SDL_CreateWindow;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		return Error::SDL_CreateRenderer;
	}

	void* memory = mmap(
		nullptr,
		1024 * 768 * 4,
		PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS,
		-1,
		0);
	if (memory == (void*)-1)
	{
		return Error::mmap;
	}

	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		1024, 768);
	if (texture == nullptr)
	{
		return Error::SDL_CreateTexture;
	}

	if (SDL_UpdateTexture(
		texture,
		nullptr,
		memory,
		1024 * 4) != 0)
	{
		return Error::SDL_UpdateTexture;
	}

	bool app_running = true;
	while (app_running)
	{
		SDL_Event event = {};
		if (SDL_WaitEvent(&event) == 0)
		{
			return Error::SDL_WaitEvent;
		}

		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_Log("window event: SDL_WINDOWEVENT_CLOSE");
				app_running = false;
			}
		}

		if (SDL_RenderCopy(renderer, texture, nullptr, nullptr) != 0)
		{
			return Error::SDL_RenderCopy;
		}
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	SDL_Log("bye bye");
	return 0;
}