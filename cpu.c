#include "cpu.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

#include "cartridge.h"
#include "cartridge_header.h"
#include "cpu_opcode_maps.h"

GameBoy_CPU_t cpu;

bool is_gbc_mode = false;
uint8_t cpu_instruction_counter = 0;

static CPU_Instruction_t fetch_instruction(uint8_t *cartridge) {
    // TODO: read from memory bus instead of directly from ROM data
    uint8_t op_code = cartridge[cpu.pc.value];
    cpu.pc.value++;
    
    const CPU_Instruction_t instruction = cpu_opcode_map[op_code];
    return instruction;
}

static bool execute_instruction(CPU_Instruction_t instruction) {
    opcode_handler handler = instruction.handler;
    if (handler == NULL) {
        SDL_Log("Unknown instruction at: %04X (%s), count: %i", cpu.pc.value,
                instruction.disassembly, cpu_instruction_counter);
        return false;
    }
    
    handler();
    return true;
}

void cpu_post_bootrom_setup(uint8_t *cartridge) {
    Cartridge_Header_t *header = CartridgeHeaderFromCartridge(cartridge);
    
    is_gbc_mode = (header->cgb_flag & 0x80);  // 0x80 indicates GBC support
    if (is_gbc_mode) {
        // Post-Boot ROM values for a Game Boy Color (CGB)
        cpu.af.value = 0x11B0;  // A = 0x11 (CGB flag indicator)
        cpu.bc.value = 0x0000;
        cpu.de.value = 0xFF56;
        cpu.hl.value = 0x000D;
    } else {
        // Post-Boot ROM values for an original Game Boy (no color).
        cpu.af.value = 0x01B0;  // A = 0x01 indicating a non-color gameboy
        cpu.bc.value = 0x0013;
        cpu.de.value = 0x00D8;
        cpu.hl.value = 0x014D;
    }

    cpu.sp.value = 0xFFFE;  // This points to the top of High RAM (HRAM), which grows downwards as functions are called.
    cpu.pc.value = 0x0100;  // Entry point in the cartridge header to start execution from.
}

bool cpu_fetch_and_execute(uint8_t *cartridge) {
    CPU_Instruction_t instruction = fetch_instruction(cartridge);
    return execute_instruction(instruction);
}
