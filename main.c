#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }
    
    current_cartridge = open_cartridge_file();
    if (current_cartridge != NULL) {
        print_cartridge_header(current_cartridge);
    }
    free(current_cartridge);
    
    SDL_Quit();
    
    return 0;
}
