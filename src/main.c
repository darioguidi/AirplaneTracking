#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "window.h"
#include "render.h"

int main(void)
{
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

    // Variabili
    int running = 1;
    char state[50];
    char comando[100];

    while(1){
        // Interazione utente scelta dei fligths da visulaizzare (filtrati per paese)
        printf("Inserire i voli di quale paese visualizzare: \n");
        fgets(state, sizeof(state), stdin);
        state[strcspn(state, "\n")] = '\0';
    
        // Chiamata allo script python per scaricare i dati interessati
        snprintf(comando, sizeof(comando), "python3 python/fetch_fligths.py %s", state);
        system(comando);

        // Lettura del fetch dei dati, associandolo ad un array
        FILE* f = fopne("data/data.json");
        

        while(running){
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT){
                    printf("Chiusura del programma \n");
                    running = 0;
                }


                if(event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_w){
                        // 
                    }
                }
            }

            // Imposta colore sfondo
            SDL_SetRenderDrawColor(renderer,0,0,0,255);

            // Pulisce il frame precedente
            SDL_RenderClear(renderer);

            // Avvio del rendering
            drawEarth(renderer);

            // Presenta il nuovo frame
            SDL_RenderPresent(renderer);
        }
    }
    

    
    // Distruzione di finestra e renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
