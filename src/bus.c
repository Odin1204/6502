#include "bus.h"

#include <stdint.h>

//initialise The Bus
void init_bus(struct Bus *bus, struct Cpu *cpu, struct Memory *memory){
    bus->cpu = cpu;
    bus->memory = memory;
}

uint8_t read_from_bus(struct Bus *bus, uint16_t address){
    if (address >= 0x0000 && address <= 0xFFFF)
        return read_from_memory(bus->memory, address);

    return 0x00;
}

void write_to_bus(struct Bus *bus, uint16_t address, uint8_t data){
    if (address >= 0x0000 && address <= 0xFFFF)
        return write_to_memory(bus->memory, address, data);
}

