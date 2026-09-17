#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "emulator_core.h"

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return -1;
    }
    
    int error = core_init();
    if (error != 0) {
        SDL_Quit();
        return error;
    }
    
    core_run();
    
    core_shutdown();
    SDL_Quit();
    return 0;
}
