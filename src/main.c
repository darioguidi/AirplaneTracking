#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "render.h"

int main(void)
{
    // Dimensioni iniziali della finestra (variabile - window resizable)
    int window_width = 900;
    int window_height = 900;

    // Angoli di rotazione
    float theta = 0.0f;
    float delta = 0.0f;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore di setup per SDL\n");
        return 1;
    }

    // Creazione della window
    SDL_Window* window = createWindow();

    if (window == NULL) {
        printf("Errore in apertura della finestra \n");
        SDL_Quit();
        return 0;
    }

    SDL_Renderer* renderer = createRenderer(window);

    if (renderer == NULL){
        printf("Errore in fase di creazione del renderer \n");
        SDL_Quit();
        return 0;
    }

    // Oggetto SDL per la gestione degli eventi
    SDL_Event event;

    // Strighe di comando
    char state[50];
    char comando[100];

    // Indice per contare i voli
    int number_flights = 0;

    // Interazione utente scelta dei fligths da visulaizzare (filtrati per paese)
    printf("Inserire i voli di quale paese visualizzare: \n");
    fgets(state, sizeof(state), stdin);
    state[strcspn(state, "\n")] = '\0';

    // Chiamata allo script python per scaricare i dati interessati
    snprintf(comando, sizeof(comando), "python3 python/fetch_fligths.py %s", state);
    system(comando);

    // Lettura del fetch dei dati per contare il numero di voli
    FILE* data = fopen("data/data.txt", "r");
    if(data==NULL){
        printf("Errore in creazione oggetto di tipo FILE\n");
        return 0;
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
        return 0;
    }

    // Lettura del fetch dei dati, associandolo ad un array
    data = fopen("data/data.txt", "r");
    if(data==NULL){
        printf("Errore in creazione oggetto di tipo FILE\n");
        free(flights);
        return 0;
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
            i++; // incremento dell'indice per popolare correttamente l'array
        }
    }

    fclose(data);


    int running = 1;
    while(running){
        while(SDL_PollEvent(&event)){
            // Termine del programma
            if (event.type == SDL_QUIT){
                printf("Chiusura del programma \n");
                running = 0;
                return 0;
            }

            // Rotazione della visuale del globo
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_a){
                    // Rotazione Orizzontale
                    theta += 0.25;
                }
                if(event.key.keysym.sym == SDLK_d){
                    theta -= 0.25;
                }
                if(event.key.keysym.sym == SDLK_w){
                    // Rotazione Verticale
                    delta += 0.25;
                }
                if(event.key.keysym.sym == SDLK_s){
                    delta -= 0.25;
                }
            }

            // Resize della finestra ed aggiornamento delle dimensioni
            if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                window_width = event.window.data1;
                window_height = event.window.data2;

                // Aggiornamento del renderer con lo scaling corretto
                SDL_RenderSetLogicalSize(renderer, window_width, window_height);
            }
        }

        // Imposta colore sfondo
        SDL_SetRenderDrawColor(renderer,0,0,0,255);

        // Pulisce il frame precedente
        SDL_RenderClear(renderer);

        // Avvio del rendering
        drawEarth(renderer, window_width, window_height, theta, delta);
        drawFligths(renderer, flights, number_flights, window_width, window_height);

        // Presenta il nuovo frame
        SDL_RenderPresent(renderer);
    }
    
    
    free(flights);
    
    // Distruzione di finestra e renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
