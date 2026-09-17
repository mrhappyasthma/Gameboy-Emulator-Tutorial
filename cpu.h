#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef union {
    uint16_t value; // The full 16-bit register value
    
    struct {
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        uint8_t hi; // Upper byte
        uint8_t lo; // Lower byte
#else
        uint8_t lo; // Lower byte (Default to Little Endian for Intel/AMD/ARM)
        uint8_t hi; // Upper byte
#endif
    };
} RegisterPair_t;

typedef struct {
    RegisterPair_t af;
    RegisterPair_t bc;
    RegisterPair_t de;
    RegisterPair_t hl;
    
    RegisterPair_t sp;
    RegisterPair_t pc;
} GameBoy_CPU_t;

/**
 * We are not emulating the boot rom. Instead, set up the CPU register values
 * that are expected after the boot rom would have executed.
 */
void cpu_post_bootrom_setup(GameBoy_CPU_t *cpu, uint8_t *cartridge);

/**
 * Fetches and executes the next instruction.
 *
 * Returns `false` if it encounters an instruction that it cannot execute.
 */
bool cpu_fetch_and_execute(GameBoy_CPU_t *cpu, uint8_t *cartridge);

bool cpu_get_zero_flag(GameBoy_CPU_t *cpu);
void cpu_set_zero_flag(GameBoy_CPU_t *cpu, bool is_set);
bool cpu_get_subtract_flag(GameBoy_CPU_t *cpu);
void cpu_set_subtract_flag(GameBoy_CPU_t *cpu, bool is_set);
bool cpu_get_half_carry_flag(GameBoy_CPU_t *cpu);
void cpu_set_half_carry_flag(GameBoy_CPU_t *cpu, bool is_set);
bool cpu_get_carry_flag(GameBoy_CPU_t *cpu);
void cpu_set_carry_flag(GameBoy_CPU_t *cpu, bool is_set);
