#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#include "cartridge.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }
    
    uint8_t *cartridge = open_cartridge_file();
    if (cartridge != NULL) {
        print_cartridge_header(cartridge);
    }
    free(cartridge);
    
    SDL_Quit();
    
    return 0;
}
