#pragma once

#include <stdint.h>

extern uint32_t core_clock_counter;

extern uint8_t *current_cartridge;

/** Initializes the emulator state. */
int core_init(void);

/** Runs the main emulator loop. */
void core_run(void);

/** Gracefully cleans up the emulator. */
void core_shutdown(void);

/**
 * Advances the emulator clock by T-cycle (ticks). NOTE: there are 4 ticks in a CPU instruction (M-cycle).
 */
void core_advance_clock(uint8_t ticks);
