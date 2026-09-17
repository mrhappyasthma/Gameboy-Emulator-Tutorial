#pragma once

#include <stdint.h>

/** Reads the memory at a given address. */
uint8_t mmu_read(uint16_t address);
