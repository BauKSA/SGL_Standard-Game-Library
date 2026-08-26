#ifdef PLATFORM_DOS
#include<core/window/Window.h>
#include<types/Memory.h>

static WindowHandle window = NULL;

fxmem_int Window_Init(Window_Config* config) {
    return 0;
}

void Window_Fullscreen(WindowHandle window) {
}

void Window_Windowed(WindowHandle window) {
}

void Window_Close(WindowHandle window) {
}

#endif

/*
* allegro_init();

    // 2. Instalar el teclado (y el mouse si lo vas a usar)
    install_keyboard();
    install_mouse();

    // 3. Fijar la profundidad de color antes de abrir el modo gráfico
    set_color_depth(32);

    // 4. Abrir el modo gráfico -> acá "creás la ventana"
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0) {
        // si falla el modo ventana, probamos con GFX_SAFE como respaldo
        if (set_gfx_mode(GFX_SAFE, 640, 480, 0, 0) != 0) {
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
            allegro_message("No se pudo iniciar el modo gráfico:\n%s\n",
                             allegro_error);
            return 1;
        }
    }

    // 5. Loop principal: pintamos algo en el buffer de pantalla
    clear_to_color(screen, makecol(0, 0, 0));
    textout_centre_ex(screen, font, "Hola, Allegro!",
                       SCREEN_W / 2, SCREEN_H / 2,
                       makecol(255, 255, 255), -1);

    readkey(); // espera a que apretes una tecla

*/