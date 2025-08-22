#include <stdio.h>
#include <SDL2/SDL.h>
#include "window.c"
#include "render.c"

int main(void)
{
    // Creazione della window
    SDL_Window* window = createWindow();

    if (window == NULL) {
        printf("Errore in apertura della finestra \n");
        return 0;
    }

    SDL_Renderer* renderer = createRenderer(window);

    if (renderer == NULL){
        printf("Errore in fase di creazione del renderer \n");
        return 0;
    }

    



    // Distruzione di finestra e renderer
    destroyWindow(window);
    destroyRenderer(renderer);

    return 0;
}
