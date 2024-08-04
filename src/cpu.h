#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Cpu
{
    /* Registers */
    uint16_t programm_counter;
    uint8_t stack_pointer;
    uint8_t accumulator;
    uint8_t x;
    uint8_t y;
    uint8_t status;

    /*STATUS:
        Carry: bit 0
        Zero: bit 1
        Interupt Disable: bit 2
        Decimal Mode: bit 3
        Break Command: bit 4
        none: bit 5
        Overflow Flag: bit 6
        Negative Flag: bit 7*/
};

//Flags
#define C 0
#define Z 1 
#define I 2
#define D 3
#define B 4
#define O 6
#define N 7



void set_status_flag(uint8_t flag, uint8_t val);

#endif