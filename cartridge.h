#pragma once

#include <stdbool.h>
#include <stdint.h>

/**
 * Requests a file path and loads the cart. Returns the cartridge or NULL in an error.
 *
 * WARNING: The memory is allocated with `malloc` and must be freed by the caller.
 */
uint8_t *open_cartridge_file();

extern uint8_t *current_cartridge;
