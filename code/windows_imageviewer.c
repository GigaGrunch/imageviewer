#include "../../SDL/include/SDL.h"
#include "imageviewer.c"
#include "windows.h"

int WinMain(void)
{
	printf("hello world!\n");

	int result = imageviewer_main();

	printf("bye bye\n");
	return result;
}
