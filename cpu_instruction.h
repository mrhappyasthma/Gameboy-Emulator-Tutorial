#pragma once

#include <stdint.h>

typedef void(*opcode_handler)(void);

typedef struct {
    // The human-readable version of the instruction, primarily for debugging. e.g. "NOP", "LD B, C"
    char *disassembly;
    
    // The number of bytes of operands that this instruction requires.
    uint8_t operand_length;
    
    // Function pointer memory address for handling this instruction.
    opcode_handler handler;
} CPU_Instruction_t;
