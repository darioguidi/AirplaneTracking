#include <stdio.h>
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

    SDL_Event event;
    int running = 1;

    // Interazione utente scelta dei fligths da visulaizzare (filtrati per paese)
    printf("Inserire i voli di quale paese visualizzare: \n");

    while(running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                printf("Chiusura del programma \n");
                running = 0;
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

    
    // Distruzione di finestra e renderer
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
