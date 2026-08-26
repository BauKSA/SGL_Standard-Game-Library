#ifndef _WINDOW_H_
#define _WINDOW_H_
#include<types/Memory.h>

static WindowHandle window;

typedef enum WINDOW_MODE {
	WINDOWED,
	FULLSCREEN
} WINDOW_MODE;

typedef struct Window_Config {
	const char* title;
	int width;
	int height;
	WINDOW_MODE mode;
} Window_Config;

fxmem_int Window_Init(Window_Config* config);
void Window_Fullscreen(WindowHandle window);
void Window_Windowed(WindowHandle window);

void Window_Close(WindowHandle window);

#endif // _WINDOW_H_