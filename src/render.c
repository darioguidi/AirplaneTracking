// Gestione del disegno in fase di rendering
#include "render.h"
#include <math.h>

// Creazione del renderer
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void drawPoint(SDL_Renderer* renderer, Point* point, int window_width, int window_height, float user_theta, float user_delta)
{
    // Centro della sfera (stesso di drawEarth)
    float z_center = 300.0f;

    // Sposto il punto rispetto al centro della sfera
    float x_local = point->x;
    float y_local = point->y;
    float z_local = point->z - z_center;

    // Rotazione orizzontale attorno all’asse Y
    float x_rot = x_local * cosf(user_theta) + z_local * sinf(user_theta);
    float z_rot = -x_local * sinf(user_theta) + z_local * cosf(user_theta);

    // Rotazione verticale attorno all’asse X
    float y_rot = y_local * cosf(user_delta) - z_rot * sinf(user_delta);
    float z_final = y_local * sinf(user_delta) + z_rot * cosf(user_delta);

    // Riporto al sistema globale aggiungendo il centro
    float x_final = x_rot;
    float y_final = y_rot;
    float z_global = z_center + z_final;

    // Traslazione dei punti per centrarli alla finestra
    float offset_x = window_width/2;
    float offset_y = window_height/2;

    // Definizione dei "punti proiettati"
    float scale = 300.0; // Distanza della camera

    float denom = (z_global / scale + 1.0f);
    if (denom <= 0.1f) denom = 0.1f; 
    float x_proj = x_final / denom;
    float y_proj = y_final / denom;

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

    // Angolo aureo su cui si basa la sequenza di fibonacci
    const float golden_angle = PI * (3.0f - sqrtf(5.0f));

    for (int i = 0; i < max_point_sphere; i++) {
        float y = 1.0f - (i / (float)(max_point_sphere - 1)) * 2.0f; 
        float radius = sqrtf(1.0f - y * y);

        float theta = golden_angle * i;

        float x = cosf(theta) * radius;
        float z = sinf(theta) * radius;

        sphere[i].x = raggio * x;
        sphere[i].y = raggio * y;
        sphere[i].z = z_center + raggio * z;
        sphere[i].type = 't';

        drawPoint(renderer, &sphere[i], window_width, window_height, user_theta, user_delta);
    }
    free(sphere);
}

void drawFligths(SDL_Renderer* renderer, Point* flights, int number_fligths, float window_width, float window_height, float user_theta, float user_delta)
{
    for(int i = 0; i<number_fligths; i++){
        drawPoint(renderer, &flights[i], window_width, window_height, user_theta, user_delta);
    }
}
