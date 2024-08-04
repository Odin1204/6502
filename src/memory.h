#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define DATA 0xFFFF-0x0206

/*64KB of memory 
0x0 to 0xFF is the zero page for the ZP0 address mode
0x100 to 0x1FF is the stack
0xFFFA to 0xFFFF are the last six bytes of memory
0x0200 to 0xFFF9 are for normal data*/
struct Memory
{
    /* pages */
    uint8_t zero_page[0x100];
    uint8_t stack[0x100];
    uint8_t last_six[0x06];
    uint8_t data[DATA];
};

void reset_memory(struct Memory *mem);

uint8_t read_from_memory(struct Memory *mem, uint16_t address);
void write_to_memory(struct Memory *mem, uint16_t address, uint8_t data);


#endif