#include "../../SDL/include/SDL.h"
#include "imageviewer.c"
#include "windows.h"

int WinMain(void)
{
	printf("ImageViewer for Windows says 'hello!'\n");

	int result = imageviewer_main();

	printf("ImageViewer for Windows says 'bye bye'\n");
	return result;
}
