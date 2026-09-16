#include <stdint.h>

typedef union {
    uint16_t reg; // The full 16-bit register value
    
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
    
    uint16_t sp;
    uint16_t pc;
} GameBoy_CPU_t;

extern GameBoy_CPU_t cpu;
