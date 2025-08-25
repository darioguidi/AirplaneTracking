// Gestione del disegno in fase di rendering
#include <stdio.h>
#include <SDL2/SDL.h>
#include "window.h"

#define PI 3.14

typedef struct{
    int x;
    int y;
    int z;
    char type;
} Point;

// Creazione della finestra
SDL_Renderer* createRenderer(SDL_Window* window);

// Disegno del singolo punto
void drawPoint(SDL_Renderer* renderer, Point* point, int window_width, int window_height, float user_theta, float user_delta);

// Disegno del globo
void drawEarth(SDL_Renderer* renderer, int window_width, int window_height, float user_theta, float user_delta);

// Disegno dei voli
void drawFligths(SDL_Renderer* renderer, float window_width, float window_height, float user_theta, float user_delta);