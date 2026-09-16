#include <stdlib.h>

#include "cpu.h"

#include "cartridge.h"
#include "cartridge_header.h"

GameBoy_CPU_t cpu;

uint8_t cpu_current_op_code = 0;
uint8_t cpu_instruction_counter = 0;
void *cpu_current_instruction_execute = NULL;

static void cpu_fetch() {
    cpu_current_op_code = current_cartridge[cpu.pc];
    cpu.pc++;
}

static void cpu_execute() {
    
}
