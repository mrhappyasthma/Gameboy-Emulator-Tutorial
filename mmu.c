#include "mmu.h"

#include <stdint.h>

#include "emulator_core.h"

// TODO: implement bank switching
static uint8_t current_rom_bank = 1;

uint8_t mmu_read(uint16_t address) {
    // ROM Bank 0 (fixed0
    if (address >= 0x0000 && address <= 0x3FFF) {
        return current_cartridge[address];
    }
       
    // Switchable Cartridge ROM Bank
    if (address >= 0x4000 && address <= 0x7FFF) {
        uint32_t actual_rom_offset = (current_rom_bank * 0x4000) + (address - 0x4000);
        return current_cartridge[actual_rom_offset];
    }

    
    // TODO: Implement VRAM (0x8000-0x9FFF), WRAM (0xC000-0xDFFF), HRAM (0xFF80-0xFFFE) etc.
    // Returning 0x00 or 0xFF is standard for unmapped or open-bus memory regions
    return 0x00;
}
