#include <SDL3/SDL.h>

#include "cartridge_header.h"

const int CART_ENTRY_POINT = 0x100;

Cartridge_Header_t *CartridgeHeaderFromCartridge(const uint8_t *cartridge) {
    if (cartridge == NULL) {
        return NULL;
    }
    return (Cartridge_Header_t *)(cartridge + CART_ENTRY_POINT);
}

void print_cartridge_header(const uint8_t *cartridge) {
    Cartridge_Header_t *header = CartridgeHeaderFromCartridge(cartridge);
    
    SDL_Log("--- CARTRIDGE HEADER INFO ---\n");
    SDL_Log("Entry Point:      0x%.2X%.2X%.2X%.2X\n",
            header->entry_point[0], header->entry_point[1],
            header->entry_point[2], header->entry_point[3]);
    
    // Clean string printing for title (forced null-termination safety)
    char clean_title[16] = {0};
    SDL_snprintf(clean_title, sizeof(clean_title), "%.15s", header->title);
    SDL_Log("Title:            %.11s\n", clean_title);
    SDL_Log("Manufacturer:     %.4s\n", &header->title[11]);
    SDL_Log("Title (full):            %s\n", clean_title);
    
    SDL_Log("CGB Flag:         0x%.2X (%s)\n", header->cgb_flag,
            (header->cgb_flag == 0x80) ? "CGB Enhanced" : (header->cgb_flag == 0xC0) ? "CGB Only" : "Non-CGB");
    
    SDL_Log("New Licensee:     %c%c\n", header->new_licensee_code[0], header->new_licensee_code[1]);
    SDL_Log("SGB Flag:         0x%.2X (%s)\n", header->sgb_flag, (header->sgb_flag == 0x03) ? "SGB Support" : "No SGB");
    SDL_Log("Cartridge Type:   0x%.2X\n", header->cartridge_type);
    
    // Calculate and display computed ROM size
    uint32_t real_rom_size = 32 * (1 << header->rom_size);
    SDL_Log("ROM Size:         0x%.2X (%d KiB)\n", header->rom_size, real_rom_size);
    SDL_Log("RAM Size:         0x%.2X\n", header->ram_size);
    SDL_Log("Destination:      0x%.2X (%s)\n", header->destination_code, (header->destination_code == 0x00) ? "Japan" : "Overseas");
    SDL_Log("Old Licensee:     0x%.2X\n", header->old_licensee_code);
    SDL_Log("Mask ROM Version: 0x%.2X\n", header->mask_rom_version_number);
    SDL_Log("Header Checksum:  0x%.2X\n", header->header_checksum);
    
    // Reconstruct the 16-bit big-endian value manually
    uint16_t global_checksum = (header->global_checksum[0] << 8) | header->global_checksum[1];
    SDL_Log("Global Checksum:  0x%.4X\n", global_checksum);
    SDL_Log("-----------------------------\n");
}
