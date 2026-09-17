#pragma once

#include "cpu.h"

// 0x00 - NOP
void cpu_no_op(GameBoy_CPU_t *cpu);

// 0xC2 - JP NZ (Jump if not zero )
void cpu_jump_if_not_zero(GameBoy_CPU_t *cpu);

// 0xC3 - JP (unconditional jump)
void cpu_unconditional_jump(GameBoy_CPU_t *cpu);
