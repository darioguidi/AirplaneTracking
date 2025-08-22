// Gestione della finestra e relativa distruzione
#include "window.h"

// Creazione della finestra con parametri passati come define
SDL_Window* createWindow (void)
{
    SDL_Window* window = SDL_CreateWindow(
        "Airplane Tracking",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        0
    );

    return window;
}

// Metodo per la distruzione della finestra
void destroyWindow(SDL_Window* window)
{
    SDL_DestroyWindow(window);
}



    