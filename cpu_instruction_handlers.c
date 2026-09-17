#include "cpu_instruction_handlers.h"

#include "emulator_core.h"

// 0x0 - NOP
// 1    1
// - - - -
void cpu_noop(void) {
    core_advance_clock(/*ticks=*/4);
}
