#include "cartridge-header.h"

const int CART_ENTRY_POINT = 0x100;

Cartridge_Header_t *CartridgeHeaderFromCartridge(const uint8_t *cartridge) {
    return (Cartridge_Header_t *)(cartridge + CART_ENTRY_POINT);
}
