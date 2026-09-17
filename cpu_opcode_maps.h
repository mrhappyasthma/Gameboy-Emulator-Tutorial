#pragma once

#include "cpu_instruction.h"

// A lookup table using the 8-bit op code (0x00 - 0xFF).
// NOTE: opcode `0xCB` indicates that "extended" instructions
extern const CPU_Instruction_t cpu_opcode_map[256];

extern const CPU_Instruction_t cpu_extended_opcode_map[256];
