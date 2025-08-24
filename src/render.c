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
    float z_center = 0;

    // Numero totale di punti da dover rappresentare sulla sfera
    int max_point_sphere = 500;
    Point* sphere = malloc(max_point_sphere*sizeof(Point));

    // Generazione dei punti globalidi una sfera centrata nella finestra 
    float raggio = WINDOW_WIDTH/2;
    float theta = 0;
    float phi = 0;

    int n_phi = 50;                          // Suddivisioni angolo phi
    int n_theta = max_point_sphere / n_phi; // Suddivisioni angolo theta

    float delta_theta = PI / (n_theta - 1);
    float delta_phi = 2 * PI / n_phi;

    for(int i=0; i<max_point_sphere; i++){

        int theta_idx = i / n_phi;
        int phi_idx = i % n_phi;

        theta = theta_idx * delta_theta;
        phi = phi_idx * delta_phi;

        sphere[i].x = x_center + raggio * sinf(theta) * cosf(phi);
        sphere[i].y = y_center + raggio * sinf(theta) * sinf(phi);
        sphere[i].z = z_center + raggio * cosf(theta);

        drawPoint(renderer, &sphere[i]);
    }
    free(sphere);
}



