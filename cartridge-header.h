#pragma once

#include <stdint.h>

// https://gbdev.io/pandocs/The_Cartridge_Header.html
typedef struct cartridge_header {
    // 0100-0103 entry point
    //
    // After displaying the nintendo logo, the built-in boot ROM jumps to address $0100, which should contain
    // a jump into the actual main program in the catridge. Most commercial games fill in this 4-byte area
    // with a nop instruction followed by jp $0150.
    uint8_t entry_point[4];
    
    // 0104-0133Nintendo logo
    //
    // This area contains a bitmap image that is displayed when the Game Boy is powered on. It must match the hex
    // of the nitnendo logo or the boot ROM won't allow the game to run.
    uint8_t nintendo_logo[48];
    
    // 0134-0142 - Title / Manufacturer code
    //
    // The game title in uppercase ASCII. If the title is less than 16 characters, the remaining bytes should
    // be padded with $00's.
    uint8_t title[15];
    
    // 0143 - Gameboy Color flag
    //
    // In modern games this is used to determine whether to enable color mode or to fall back to monochrome mode.
    // Bit 7 will trigger a write of this register value to the KEY0 register which sets the CPU mode.
    //
    // $80 -> supports CGB enchancements but is backwards compatible with monochrome gameboys
    // $C0 -> only supports GBC
    uint8_t cgb_flag;
    
    // 0144-0145 New licensee code
    //
    // This area contains a 2-digit ASCII code indicating the game's publisher. IT is only meaningful if the
    // `old_licensee' is exactly $33 (which is the case for all games made after the super gameboy release).
    // Otherwise it must read the old code.
    uint8_t new_licensee_code[2];
    
    // 0146 - Super Game Boy flag
    //
    // This bype specifies whether the game suppoers SGB functions. Must be $03, or else it will be ignored.
    uint8_t sgb_flag;
    
    // 0147 - Cartridge Type
    //
    // This byte indicates what kind of hardware is present on the carridge. Most notably it's memory bank
    // controller, RAM, etc.
    uint8_t cartridge_type;
    
    // 0148 - ROM size
    //
    // This byte indicates how much ROM is present on the cartridge. The rom size is usually given by
    // 32 KiB * (1 << value).
    uint8_t rom_size;
    
    // 0149 - RAM size
    //
    // This byte indicates how much RAM is present on the cartridge (if any).
    uint8_t ram_size;
    
    // 014A - Destination Code
    //
    // This byet specifies whether this version is intended to be sold in Japan ($00) or overseas ($01).
    uint8_t destination_code;
    
    // 014B - Old licensee code
    //
    // This byte is used in older (pre-SGB) cartridges to specify the games publisher. $33 indicates that the
    // `new_licensee_code` should be used.
    uint8_t old_licensee_code;
    
    // 014C - Mask ROM version number
    //
    // This byte specifies the versoin number of the game. It is usually $00.
    uint8_t mask_rom_version_number;
    
    // 014D - Header checksum
    //
    // This byte contains the 8-bit checksum computed from the cartridge header bytes $0134-014C. The boot ROM
    // computes the checksum as follows:
    //
    // uint8_t checksum = 0;
    // for (uint16_t address = 0x0134; address <= 0x014C; address++) {
    //   checksum = checksum - rom[address] - 1;
    // }
    //
    // If the byte at $014D does not match the lower 8 bits of checksum, then the boot ROM will lock up.
    uint8_t header_checksum;
    
    // 014E-014F - Global Checksum
    //
    // Contains the big-endian bits of the checksum of all the bytes of the cartridge ROM (except for these
    // two bits).
    //
    // NOTE: This checksum is not verified normally, except for Pokemon Stadium's "GB Tower" emulator.
    uint8_t global_checksum[2];
} Cartridge_Header_t;

Cartridge_Header_t *CartridgeHeaderFromCartridge(const uint8_t *cartridge);
