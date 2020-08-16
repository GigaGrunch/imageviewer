#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8;

typedef enum
{
	Error_malloc = 1,
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
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Pixel;

void imageviewer_main(void);
