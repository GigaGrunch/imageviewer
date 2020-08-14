#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8;

typedef enum
{
	Error_malloc,

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
	// I actually don't know, why these are inversed.
	// Something, something, endianness.
	u8 a;
	u8 b;
	u8 g;
	u8 r;
} Pixel;

int imageviewer_main(void);
