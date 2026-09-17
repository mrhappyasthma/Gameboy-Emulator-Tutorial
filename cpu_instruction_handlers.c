#include "cpu_instruction_handlers.h"

#include <SDL3/SDL.h>

#include "cpu.h"
#include "emulator_core.h"
#include "mmu.h"

static void internal_absolute_jump(GameBoy_CPU_t *cpu, uint8_t lo, uint8_t hi) {
    cpu->pc.hi = hi;
    cpu->pc.lo = lo;
    core_advance_clock(/*ticks=*/4);
}

// 0x00 - NOP
// 1    1
// - - - -
void cpu_no_op(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }
    
    core_advance_clock(/*ticks=*/4);
}

// 0xC2 - JP NZ, a16
// 3   4/3
// - - - -
void cpu_jump_if_not_zero(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }
    
    // Extract lower 8-bit address value.
    uint8_t lo = mmu_read(cpu->pc.value);
    cpu->pc.value++;
    core_advance_clock(/*ticks=*/4);
    
    // Extract higher 8-bit address value.
    uint8_t hi = mmu_read(cpu->pc.value);
    cpu->pc.value++;
    core_advance_clock(/*ticks=*/4);
    
    bool zero_flag_set = cpu_get_zero_flag(cpu);
    if (!zero_flag_set) {
        cpu->pc.hi = hi;
        cpu->pc.lo = lo;
        core_advance_clock(/*ticks=*/4);
    }
}

// 0xC3 - JP a16
// 3   4
// - - - -
void cpu_unconditional_jump(GameBoy_CPU_t *cpu) {
    if (cpu == NULL) {
        SDL_LogError(-1, "CPU cannot be null");
        return;
    }
    
    // Extract lower 8-bit address value.
    uint8_t lo = mmu_read(cpu->pc.value);
    cpu->pc.value++;
    core_advance_clock(/*ticks=*/4);
    
    // Extract higher 8-bit address value.
    uint8_t hi = mmu_read(cpu->pc.value);
    cpu->pc.value++;
    core_advance_clock(/*ticks=*/4);
    
    cpu->pc.hi = hi;
    cpu->pc.lo = lo;
    core_advance_clock(/*ticks=*/4);
}
