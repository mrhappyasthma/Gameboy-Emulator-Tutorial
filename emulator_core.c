#include "emulator_core.h"

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"
#include "cpu.h"

static bool quit_requested = false;
static GameBoy_CPU_t *cpu = NULL;

uint8_t *current_cartridge = NULL;

uint32_t core_clock_counter = 0;

int core_init(void) {
    current_cartridge = open_cartridge_file();
    if (current_cartridge == NULL) {
        SDL_Log("Cartridge could not be opened.");
        SDL_Quit();
        return -1;
    }
    
    cpu = (GameBoy_CPU_t *)malloc(sizeof(GameBoy_CPU_t));
    
    print_cartridge_header(current_cartridge);
    return 0;
}

void core_run(void) {
    cpu_post_bootrom_setup(cpu, current_cartridge);

    while (!quit_requested) {
        if (!cpu_fetch_and_execute(cpu, current_cartridge)) {
            // Encountered an instruction that we cannot execute.
            quit_requested = true;
        }
    }
    
}

void core_shutdown(void) {
    free(current_cartridge);
    free(cpu);
}

void core_advance_clock(uint8_t ticks) {
    core_clock_counter += ticks;
}
