// Gestione del disegno in fase di rendering
#include "render.h"
#include <math.h>

// Creazione del renderer
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void drawPoint(SDL_Renderer* renderer, Point* point)
{
    // Trasformazione adeguata dei punti tridimensionali

    /// Traslazione dei punti per centrarli alla finestra
    float offset_x = WINDOW_WIDTH/2;
    float offset_y = WINDOW_HEIGHT/2;

    /// Rotazione del globo

    /// Definizione dei "punti proiettati"
    float scale = 200.0; // distanza della camera

    float x_proj = point->x / (point->z / scale + 1.0);
    float y_proj = point->y / (point->z / scale + 1.0);
    float x_delta = x_proj + offset_x;
    float y_delta = -y_proj + offset_y;

    // Oggetto SDL forma "Rettangolo"
    SDL_Rect rect = (SDL_Rect){(int)x_delta, (int)y_delta, SIZE_POINT, SIZE_POINT};

    // Colore per disegnare il punto e stampa
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

void drawEarth(SDL_Renderer* renderer)
{
    // Coordinate centro sfera
    float x_center = WINDOW_WIDTH/2;
    float y_center = WINDOW_HEIGHT/2;
    float z_center = 1;

    // Numero totale di punti da dover rappresentare sulla sfera
    int max_point_sphere = 200;
    Point* sphere = malloc(max_point_sphere*sizeof(Point));

    // Generazione dei punti globalidi una sfera centrata nella finestra 
    float raggio = WINDOW_WIDTH/2;

    for(int i=0; i<max_point_sphere; i++){
        float z = 1.0f - 2.0f*i/(max_point_sphere);
        float r = sqrtf(1 - z*z);
        float phi = PI * (1 + sqrtf(5)) * i;

        sphere[i].x = x_center + raggio * r * cosf(phi);
        sphere[i].y = y_center + raggio * r * sinf(phi);
        sphere[i].z = z_center + raggio * z;

        drawPoint(renderer, &sphere[i]);
    }
    free(sphere);
}


