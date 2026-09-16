#pragma once

#include <stdint.h>

typedef struct {
    // The human-readable version of the instruction, primarily for debugging. e.g. "NOP", "LD B, C"
    char *disassembly;
    
    // The number of bytes of operands that this instruction requires.
    uint8_t operand_length;
    
    // Function pointer memory address for handling this instruction.
    void *execute;
} CPU_Instruction_t;

// A lookup table using the 8-bit op code (0x00 - 0xFF).
// NOTE: opcode `0xCB` indicates that "extended" instructions
extern const CPU_Instruction_t instruction_opcode_map[256];
extern const CPU_Instruction_t extended_instruction_opcode_map[256];
