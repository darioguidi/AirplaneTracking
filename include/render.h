// Gestione del disegno in fase di rendering
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct{
    int x;
    int y;
    int z;
} Point;

// Creazione della finestra
SDL_Renderer* createRenderer(SDL_Window* window);

// Disegno del singolo punto
void drawPoint(SDL_Renderer* renderer, Point* point);

// Disegno del globo
