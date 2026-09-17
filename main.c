#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"
#include "cpu.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }
    
    uint8_t *cartridge = open_cartridge_file();
    if (cartridge == NULL) {
        SDL_Log("Cartridge could not be opened.");
        SDL_Quit();
        return 1;
    }
    
    print_cartridge_header(cartridge);
    
    cpu_post_bootrom_setup(cartridge);
    cpu_fetch_and_execute(cartridge);
    
    free(cartridge);
    
    SDL_Quit();
    return 0;
}
