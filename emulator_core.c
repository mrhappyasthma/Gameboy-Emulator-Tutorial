#include "emulator_core.h"

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"
#include "cpu.h"

static uint8_t *current_cartridge = NULL;
static bool quit_requested = false;

uint32_t core_clock_counter = 0;

int core_init() {
    current_cartridge = open_cartridge_file();
    if (current_cartridge == NULL) {
        SDL_Log("Cartridge could not be opened.");
        SDL_Quit();
        return -1;
    }
    
    print_cartridge_header(current_cartridge);
    return 0;
}

void core_run() {
    cpu_post_bootrom_setup(current_cartridge);

    while (!quit_requested) {
        if (!cpu_fetch_and_execute(current_cartridge)) {
            // Encountered an instruction that we cannot execute.
            quit_requested = true;
        }
    }
    
}

void core_shutdown() {
    free(current_cartridge);
}

void core_advance_cpu_clock(uint8_t ticks) {
    core_clock_counter += ticks;
}
