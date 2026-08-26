#ifdef PLATFORM_PC
#include<core/window/Window.h>
#include<types/Memory.h>

#include<SDL3/SDL_init.h>
#include<SDL3/SDL_video.h>

static WindowHandle window = NULL;

fxmem_int Window_Init(Window_Config* config) {
	if (!SDL_Init(SDL_INIT_VIDEO)) return 0;

    window = SDL_CreateWindow(
        config->title ? config->title : "[Game name] placeholder",
        config->width > 0 ? config->width : 800,
        config->height > 0 ? config->height : 600,
        config->mode == FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0
    );

    return window != NULL;
}

void Window_Fullscreen(WindowHandle window) {
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window_Windowed(WindowHandle window) {
	SDL_SetWindowFullscreen(window, 0);
}

void Window_Close(WindowHandle window) {
	SDL_DestroyWindow(window);
}

#endif