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

#endif // _WINDOW_H_