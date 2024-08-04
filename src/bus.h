#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "cpu.h"
#include "memory.h"

//struct of the Bus containing memory and the cpu
typedef struct Bus
{
    struct Cpu *cpu;
    struct Memory *memory;
};

void init_bus(Bus *bus, struct Cpu *cpu, struct Memory *memory);

uint8_t read_from_bus(Bus *bus, uint16_t address);

void write_to_bus(Bus *bus, uint16_t address, uint8_t data);

#endif