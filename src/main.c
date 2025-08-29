#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "render.h"

int main(void)
{
    // Dimensioni iniziali della finestra (variabile - window resizable)
    int window_width = 900;
    int window_height = 600;

    // Dimensioni riquadro input ed output
    int input_window_width = 300;
    int input_window_height = window_height;

    // Dimensioni sezione contenente il video della sfera
    int sphere_window_width = window_width - input_window_width;
    int sphere_window_height = window_height;


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

    // Strighe di comando per leggere la voce del menù
    char input[20];
    int choose;

    // Stringhe per comporre la richiesta al system
    char state[50];
    char comando[512];

    time_t time_last;
    time_t time_now;

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

            snprintf(comando, sizeof(comando), "python3 ./python/fetch_fligths.py \"%s\"", state);
            printf("Eseguo: %s\n", comando);
            system(comando);
            
            time_last = 0;

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
                            theta += 0.05;
                        }
                        if(event.key.keysym.sym == SDLK_d){
                            theta -= 0.05;
                        }
                        if(event.key.keysym.sym == SDLK_w){
                            // Rotazione Verticale
                            delta += 0.05;
                        }
                        if(event.key.keysym.sym == SDLK_s){
                            delta -= 0.05;
                        }
                    }

                    // Resize della finestra ed aggiornamento delle dimensioni
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                        window_width = event.window.data1;
                        window_height = event.window.data2;

                        input_window_width = 300;
                        input_window_height = window_height;     
                        
                        sphere_window_width = window_width - input_window_width;
                        sphere_window_height = window_height;

                        // Aggiornamento del renderer con lo scaling corretto
                        SDL_RenderSetLogicalSize(renderer, window_width, window_height);
                    }
                }

                time(&time_now);

                if ((time_now-time_last) >= 5) {
                    time_last=time_now;
                    system(comando);
                }
                  

                SDL_SetRenderDrawColor(renderer, 0,0,0,255);
                SDL_RenderClear(renderer);

                drawEarth(renderer, sphere_window_width, sphere_window_height, theta, delta);
                drawFligths(renderer, sphere_window_width, sphere_window_height, theta, delta);

                SDL_RenderPresent(renderer);

                SDL_Delay(16); // riduce carico CPU
                }
        }
    }

    // Distruzione di finestra e renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
