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
    // Grandezza punti della "Terra"
    float size_point;

    // Distanza della sfera dalla visuale
    float center = 300.0f;

    // Coordinate del punto 
    float x = point->x;
    float y = point->y;
    float z = point->z - center;
    
    // Trasformazione

    // Rotazione per l'asse delle X
    float x_rot = x * cosf(user_theta) + z * sinf(user_theta);
    float z_rot = -x * sinf(user_theta) + z * cosf(user_theta);
    x = x_rot;
    z = z_rot;

    // Rotazione per l'asse delle Y 
    float y_rot = y * cosf(user_delta) + z * sinf(user_delta);
    z_rot = -y * sinf(user_delta) + z * cosf(user_delta);
    y = y_rot;
    z = z_rot + center;

    // Calcolo del offset dei punti
    float offset_x = window_width / 2;
    float offset_y = window_height / 2;

    // Proiezione prospettica
    float scale = 300.0f; // distanza della camera
    float denom = 1.0f + z / scale;
    if (denom <= 0.1f) denom = 0.1f;
    float x_proj = x / denom;
    float y_proj = y / denom;

    float screen_x = x_proj + offset_x;
    float screen_y = -y_proj + offset_y;  

    // Distinzione dei punti per tipologia
    if (point->type == 't'){
        size_point = 2.0f;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else if (point->type == 'f'){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        size_point = 10.0f;
    }

    // Creazione e Stampa del rect
    SDL_Rect rect = (SDL_Rect){(int)screen_x, (int)screen_y, size_point, size_point};
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

void drawFligths(SDL_Renderer* renderer, float window_width, float window_height, float user_theta, float user_delta)
{
    int number_flights = 0;

    // Lettura del fetch dei dati per contare il numero di voli
    FILE* data = fopen("data/data.txt", "r");
    if(data==NULL){
        printf("Errore in creazione oggetto di tipo FILE\n");
    }

    // Buffer per leggere la riga
    char row[256];
    while(fgets(row, sizeof(row), data)){
        float x,y,z;
        if(sscanf(row, "%f,%f,%f", &x,&y,&z)==3){
            number_flights += 1;
        }
    }

    fclose(data);

    // Alloco lo spazio di memoria per le struct Point dei voli
    Point* flights = malloc(number_flights * sizeof(Point));
    if(flights == NULL){
        printf("Errore in allocazione memoria per i voli\n");
    }

    // Lettura del fetch dei dati, associandolo ad un array
    data = fopen("data/data.txt", "r");
    if(data==NULL){
        printf("Errore in creazione oggetto di tipo FILE\n");
        free(flights);
    }

    // Indice
    int i = 0;

    // Buffer per leggere la riga (riutilizzo lo stesso buffer)
    while(fgets(row, sizeof(row), data)){
        float x,y,z;
        if(sscanf(row, "%f,%f,%f", &x,&y,&z)==3){
            flights[i].x = x;
            flights[i].y = y;
            flights[i].z = z;
            flights[i].type = 'f';

            drawPoint(renderer, &flights[i], window_width, window_height, user_theta, user_delta);

            i++; 
        }
    }

    fclose(data);
    free(flights);
}
