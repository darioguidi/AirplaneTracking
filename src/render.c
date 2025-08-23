// Gestione del disegno in fase di rendering
#include "include/render.h"

// Creazione del renderer
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void drawPoint(SDL_Renderer* renderer, Point* point)
{
    // Trasformazione adeguata dei punti tridimensionali

    // Oggetto SDL forma "Rettangolo"
    SDL_Rect rect = (SDL_Rect){point->x, point->y};

    // Colore per disegnare il punto e stampa
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void drawEarth(SDL_Renderer* renderer){

}


