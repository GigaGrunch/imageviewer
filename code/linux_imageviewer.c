#include <SDL2/SDL.h>
#include "imageviewer.c"

int main(void)
{
	printf("ImageViewer for Linux says 'hello!'\n");

	imageviewer_main();

	printf("ImageViewer for Linux says 'bye bye'\n");
	return 0;
}
