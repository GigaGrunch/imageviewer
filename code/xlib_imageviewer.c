#include <X11/Xlib.h>
#include <stdio.h>

int main(void)
{
	printf("ImageViewer for Linux (using Xlib) says 'hello!'\n");

	Display* display = XOpenDisplay(NULL);

	printf("ImageViewer for Linux says (using XLib) 'bye bye'\n");
	return 0;
}
