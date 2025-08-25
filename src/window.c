// Gestione della finestra e relativa distruzione
#include "window.h"

// Creazione della finestra con parametri passati come define
SDL_Window* createWindow (int window_width, int window_height)
{
    SDL_Window* window = SDL_CreateWindow(
        "Airplane Tracking",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_RESIZABLE
    );

    return window;
}





    