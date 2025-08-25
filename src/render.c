// Gestione del disegno in fase di rendering
#include "render.h"
#include <math.h>

// Creazione del renderer
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void drawPoint(SDL_Renderer* renderer, Point* point, int window_width, int window_height)
{
    // Traslazione dei punti per centrarli alla finestra
    float offset_x = window_width/2;
    float offset_y = window_height/2;

    // Definizione dei "punti proiettati"
    float scale = 200.0; // Distanza della camera

    float denom = (point->z / scale + 1.0f);
    if (denom <= 0.1f) denom = 0.1f; 
    float x_proj = point->x / denom;
    float y_proj = point->y / denom;

    float x_delta = x_proj + offset_x;
    float y_delta = -y_proj + offset_y;

    // Oggetto SDL forma "Rettangolo"
    SDL_Rect rect = (SDL_Rect){(int)x_delta, (int)y_delta, SIZE_POINT, SIZE_POINT};

    // Colore per disegnare il punto e stampa
    if(point->type=='t'){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }else if(point->type=='f'){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }

    SDL_RenderFillRect(renderer, &rect);
}

void drawEarth(SDL_Renderer* renderer, int window_width, int window_height, float user_theta, float user_delta)
{
    // Numero massimo di punti sulla superficie sferica
    int max_point_sphere = 5000; 
    Point* sphere = malloc(max_point_sphere * sizeof(Point));

    // Calcolo del raggio e della distanza dalla finestra della sfera
    float raggio = window_width / 3.0f;
    float z_center = 300.0f;

    // Angolo auereo su cui si basa la sequenza di fibonacci
    const float golden_angle = PI * (3.0f - sqrtf(5.0f));

    for (int i = 0; i < max_point_sphere; i++) {
        float y = 1.0f - (i / (float)(max_point_sphere - 1)) * 2.0f; 
        float radius = sqrtf(1.0f - y * y);

        float theta = golden_angle * i;

        // Rotazione orizzontale attorno all’asse Y
        theta += user_theta;

        float x = cosf(theta) * radius;
        float z = sinf(theta) * radius;

        // Rotazione verticale attorno all’asse X
        float new_y = y * cosf(user_delta) - z * sinf(user_delta);
        float new_z = y * sinf(user_delta) + z * cosf(user_delta);

        sphere[i].x = raggio * x;
        sphere[i].y = raggio * new_y;
        sphere[i].z = z_center + raggio * new_z;
        sphere[i].type = 't';

        drawPoint(renderer, &sphere[i], window_width, window_height);
    }
    free(sphere);
}


void drawFligths(SDL_Renderer* renderer, Point* flights)
{
    

}




