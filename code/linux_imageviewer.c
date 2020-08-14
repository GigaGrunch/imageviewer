#include <SDL2/SDL.h>
#include "imageviewer.c"

int main(void)
{
	printf("hello world!\n");

	int result = imageviewer_main();

	printf("bye bye\n");
	return result;
}
