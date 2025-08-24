// Gestione della finestra e relativa distruzione
#include "window.h"

// Creazione della finestra con parametri passati come define
SDL_Window* createWindow (void)
{
    SDL_Window* window = SDL_CreateWindow(
        "Airplane Tracking",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        900,
        900,
        SDL_WINDOW_RESIZABLE
    );

    return window;
}





    