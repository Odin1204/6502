#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


struct instruction
{
    char *name;
    uint8_t (*operation)(void);
    uint8_t (*mode)(void);
    uint8_t cycles;
};


struct emulator_state
{
    uint8_t fetched; //Recently fetched data for current operation
    uint16_t addr_abs; //Absolute Address for current instruction
    uint8_t addr_rel; //Relative address for branching
    uint8_t opcode; //Current opcode being executed
};

void reset_emulator_state();

void execute_instruction(uint8_t op, uint32_t *cycles);

#endif