#include "cpu.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"
#include "cpu_opcode_maps.h"
#include "emulator_core.h"

static const uint8_t BIT_7_MASK = 0x80;
static const uint8_t BIT_6_MASK = 0x40;
static const uint8_t BIT_5_MASK = 0x20;
static const uint8_t BIT_4_MASK = 0x10;

GameBoy_CPU_t cpu;

bool is_gbc_mode = false;
uint8_t cpu_instruction_counter = 0;

static CPU_Instruction_t fetch_instruction(GameBoy_CPU_t *cpu, uint8_t *cartridge) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        CPU_Instruction_t empty_instruction;
        return empty_instruction;
    }
    
    // TODO: read from memory bus instead of directly from ROM data
    uint8_t op_code = cartridge[cpu->pc.value];
    cpu->pc.value++;
    core_advance_clock(/*ticks=*/4);
    
    const CPU_Instruction_t instruction = cpu_opcode_map[op_code];
    return instruction;
}

static bool execute_instruction(GameBoy_CPU_t *cpu, CPU_Instruction_t instruction) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    
    
    opcode_handler handler = instruction.handler;
    if (handler == NULL) {
        SDL_Log("Unknown instruction at: %04X (%s), count: %i", cpu->pc.value,
                instruction.disassembly, cpu_instruction_counter);
        return false;
    }
    
    handler(cpu);
    return true;
}

void cpu_post_bootrom_setup(GameBoy_CPU_t *cpu, uint8_t *cartridge) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }
    if (cartridge == NULL) {
        SDL_LogError(-1, "Cartridge cannot be null");
        return;
    }
    
    Cartridge_Header_t *header = CartridgeHeaderFromCartridge(cartridge);
    
    is_gbc_mode = (header->cgb_flag & 0x80);  // 0x80 indicates GBC support
    if (is_gbc_mode) {
        // Post-Boot ROM values for a Game Boy Color (CGB)
        cpu->af.value = 0x11B0;  // A = 0x11 (CGB flag indicator)
        cpu->bc.value = 0x0000;
        cpu->de.value = 0xFF56;
        cpu->hl.value = 0x000D;
    } else {
        // Post-Boot ROM values for an original Game Boy (no color).
        cpu->af.value = 0x01B0;  // A = 0x01 indicating a non-color gameboy
        cpu->bc.value = 0x0013;
        cpu->de.value = 0x00D8;
        cpu->hl.value = 0x014D;
    }

    cpu->sp.value = 0xFFFE;  // This points to the top of High RAM (HRAM), which grows downwards as functions are called.
    cpu->pc.value = 0x0100;  // Entry point in the cartridge header to start execution from.
}

bool cpu_fetch_and_execute(GameBoy_CPU_t *cpu, uint8_t *cartridge) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    if (cartridge == NULL) {
        SDL_LogError(-1, "Cartridge cannot be null");
        return false;
    }
    
    CPU_Instruction_t instruction = fetch_instruction(cpu, cartridge);
    return execute_instruction(cpu, instruction);
}

// Returns true if bit 7 is 1, else false.
bool cpu_get_zero_flag(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    
    return (cpu->af.lo & BIT_7_MASK) != 0;
}

void cpu_set_zero_flag(GameBoy_CPU_t *cpu, bool is_set) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }
    
    cpu->af.lo &= ~BIT_7_MASK;  // Clear bit 7 (0111 1111)
    
    cpu->af.lo |= ((uint8_t)is_set << 7);
}

// Returns true if bit 6 is 1, else false.
bool cpu_get_subtract_flag(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    
    return (cpu->af.lo & BIT_6_MASK) != 0;
}

void cpu_set_subtract_flag(GameBoy_CPU_t *cpu, bool is_set) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }

    cpu->af.lo &= ~BIT_6_MASK;  // Clear bit 6 (1011 1111)
    
    cpu->af.lo |= ((uint8_t)is_set << 6);
}

// Returns true if bit 5 is 1, else false.
bool cpu_get_half_carry_flag(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    
    return (cpu->af.lo & BIT_5_MASK) != 0;
}

void cpu_set_half_carry_flag(GameBoy_CPU_t *cpu, bool is_set) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }

    cpu->af.lo &= ~BIT_5_MASK;  // Clear bit 5 (1101 1111)
    
    cpu->af.lo |= ((uint8_t)is_set << 5);
}

// Returns true if bit 4 is 1, else false.
bool cpu_get_carry_flag(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return false;
    }
    
    return (cpu->af.lo & BIT_4_MASK) != 0;
}

void cpu_set_carry_flag(GameBoy_CPU_t *cpu, bool is_set) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }

    cpu->af.lo &= ~BIT_4_MASK;  // Clear bit 4 (1110 1111)
    
    cpu->af.lo |= ((uint8_t)is_set << 4);
}
