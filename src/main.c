#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "render.h"

int main(void)
{
    // Dimensioni iniziali della finestra (variabile - window resizable)
    int window_width = 600;
    int window_height = 600;

    // Angoli di rotazione
    float theta = 0.0f;
    float delta = 0.0f;

    // Inizializzazione del motore grafico SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore di setup per SDL\n");
        return 1;
    }

    // Creazione della window
    SDL_Window* window = createWindow(window_width, window_height);

    if (window == NULL) {
        printf("Errore in apertura della finestra \n");
        SDL_Quit();
        return 0;
    }

    // Creazione del renderer (rendering)
    SDL_Renderer* renderer = createRenderer(window);

    if (renderer == NULL){
        printf("Errore in fase di creazione del renderer \n");
        SDL_Quit();
        return 0;
    }

    // Oggetto SDL per la gestione degli eventi
    SDL_Event event;

    // Strighe di comando
    char input[20];
    int choose;
    char state[50];
    char comando[100];

    while(1){
        printf("MENU' \n - 0 Chiusura applicazione\n - 1 Scelta del paese voli da visualizzare\n - 2 Mostra Lista dei paesi con voli attivi\n");
        fgets(input, sizeof(input), stdin);
        choose=atoi(input);

        if(choose==0){
            return 0;
        }else if(choose==1){
            // Interazione utente scelta dei fligths da visulaizzare (filtrati per paese)
            printf("Inserire i voli di quale paese visualizzare: \n");
            fgets(state, sizeof(state), stdin);
            state[strcspn(state, "\n")] = '\0';

            // Chiamata allo script python per scaricare i dati interessati
            snprintf(comando, sizeof(comando), "python3 python/fetch_fligths.py %s", state);
            system(comando);

            int running = 1;
            while(running){
                while(SDL_PollEvent(&event)){
                    // Termine del programma
                    if (event.type == SDL_QUIT){
                        printf("Chiusura del processo \n");
                        running = 0;
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
                drawFligths(renderer, window_width, window_height, theta, delta);

                // Presenta il nuovo frame
                SDL_RenderPresent(renderer);
            }
        }
    }

    // Distruzione di finestra e renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
