#define CPU_INTERNAL_ACCESS
#define LOGMODE //comment to disable logmode

#include "instructions.h"
#include "bus.h"
#include "memory.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Cpu cpu;
struct Memory mem;
struct Bus bus;


uint8_t cycles; //Counts how many cycles the current instruction has remaining
uint32_t clock_count; //Current clock cycle

//functions to set flags and extract it
uint8_t set_bit(uint8_t *num_p, uint8_t bit){
    *num_p = *num_p | 1 << bit;
    return *num_p;
}

uint8_t reset_bit(uint8_t *num_p, uint8_t bit){
    *num_p = *num_p & ~(1 << bit);
    return *num_p;
}

uint8_t set_status_flag(uint8_t flag, uint8_t val){
    if (val != 1 && val != 0)
        return 1;
    
    if (flag >= 0 && flag < 8 && flag != 5) {
        if (val == 1)
            set_bit(&cpu.status, flag);
        else
            reset_bit(&cpu.status, flag);
        return 0;
    }
    else
        return 1;       
}

uint8_t extract_flag(uint8_t flag){
    return ((cpu.status >> flag) & 1);
}



//resets all registers and emulator variables to a predetermint state and re-initialises the bus
void cpu_reset(){

    cpu.program_counter = 0x8000;
    
    cpu.accumulator = 0x0;
    cpu.x = 0x0;
    cpu.y = 0x0;
    cpu.status = 0x0;
    cpu.stack_pointer = 0xFF;

    reset_emulator_state();
    init_bus(&bus, &cpu, &mem);

    clock_count = 0;
    cycles = 8;
}

void total_reset(){
    reset_memory(&mem);
    cpu_reset();
}

//read from the bus and return the data
uint8_t cpu_read(uint16_t address){
    return read_from_bus(&bus, address);
}

//write to the bus
void cpu_write(uint16_t address, uint8_t data){
    write_to_bus(&bus, address, data);
}

/*one clock cycle. 
  If cycles are zero the program fetches a new opcode from the program counter and executes the instruction*/
void clock(){
    uint8_t opcode;

    if (cycles == 0){
        #ifdef LOGMODE
        printf("\nNEW INSTRUCTION:\n\n");
        #endif

        opcode = cpu_read(cpu.program_counter++);


        execute_instruction(opcode, &cycles);

        #ifdef LOGMODE //if logmode is enabled print   

        printf("\n Opcode: %x, cycles: %d\n", opcode, cycles);

        printf("\nRegisters:");
        printf("\nAccumulator: %x, X: %x, Y: %x", cpu.accumulator, cpu.x, cpu.y);
        printf("\nProgram Counter: %x, Status: %x\n", cpu.program_counter, cpu.status);
        printf("\nEND OF INSTRUCTION\n\n");

        #endif
    }

    cycles--;
    clock_count++;
}

