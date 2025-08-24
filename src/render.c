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

    /// Definizione dei "punti proiettati"
    float scale = 200.0; // distanza della camera

    float denom = (point->z / scale + 1.0f);
    if (denom <= 0.1f) denom = 0.1f; 
    float x_proj = point->x / denom;
    float y_proj = point->y / denom;
    float x_delta = x_proj + offset_x;
    float y_delta = -y_proj + offset_y;

    // Oggetto SDL forma "Rettangolo"
    SDL_Rect rect = (SDL_Rect){(int)x_delta, (int)y_delta, SIZE_POINT, SIZE_POINT};

    // Colore per disegnare il punto e stampa
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void drawEarth(SDL_Renderer* renderer)
{
    int max_point_sphere = 200; 
    Point* sphere = malloc(max_point_sphere * sizeof(Point));

    float raggio = WINDOW_WIDTH / 3.0f;
    float z_center = 500.0f;

    const float golden_angle = PI * (3.0f - sqrtf(5.0f));

    for (int i = 0; i < max_point_sphere; i++) {
        float y = 1.0f - (i / (float)(max_point_sphere - 1)) * 2.0f; // da 1 a -1
        float radius = sqrtf(1.0f - y * y);

        float theta = golden_angle * i;

        float x = cosf(theta) * radius;
        float z = sinf(theta) * radius;

        sphere[i].x = raggio * x;
        sphere[i].y = raggio * y;
        sphere[i].z = z_center + raggio * z;

        drawPoint(renderer, &sphere[i]);
    }
    free(sphere);
}




