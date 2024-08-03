#include "cpu.h"
#include "instructions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct CPU cpu;

uint8_t cycles; //Counts how many cycles the current instruction has remaining
uint32_t clock_count; //Current clock cycle

int set_status_flag(uint8_t flag, uint8_t val){
    if (val != 1 && val != 0)
        return 1;
    
    if (flag >= 0 && flag < 8 && flag != 5) {
        if (val == 1)
            set_bit(cpu.status, flag);
        else
            reset_bit(cpu.status, flag);
        return 0;
    }
    else
        return 1;       
}

void set_bit(uint8_t num, uint8_t bit){
    num = num | 1 << bit;
}

void reset_bit(uint8_t num, uint8_t bit){
    num = num & ~(1 << bit);
}

//resets all registers and emulator variables to a predetermint state
void cpu_reset(){

    cpu.programm_counter = 0x8000;
    
    cpu.accumulator = 0x0;
    cpu.x = 0x0;
    cpu.y = 0x0;
    cpu.status = 0x0;
    cpu.stack_pointer = 0xFD;

    reset_emulator_state();

    clock_count = 0;
    cycles = 8;
}

int main()
{
    return 0;
}