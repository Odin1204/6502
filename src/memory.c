#include "memory.h"

#include <stdint.h>
#include <stdlib.h>

void reset_memory(struct Memory *mem){
    int i;
    for (i; i < DATA; i++){
        if (i < 0x06)
            mem->last_six[i] = 0x00;
        if (i < 0x0100){
            mem->zero_page[i] = 0x00;
            mem->stack[i] = 0x00;
        }

        mem->data[i] = 0x00;
    }    
}

//returns pointer to the desired element in memory
int *get_memory_address_pointer(struct Memory *mem, uint16_t address){
    if (address < 0x0100)
        return mem->zero_page+address;
    else if (address < 0x0200)
        return mem->stack+(address-0x0100);
    else if (address > 0xFFF9)
        return mem->last_six+(address-0xFFF9);
    else
        return mem->data+(address-0x0200);
}

uint8_t read_from_memory(struct Memory *mem, uint16_t address){
    int *pointer_to_address = get_memory_address_pointer(mem, address);
    return *pointer_to_address;
}

void write_to_memory(struct Memory *mem, uint16_t address, uint8_t data){
    int *pointer_to_adress = get_memory_address_pointer(mem, address);
    *pointer_to_adress = data;
    return;
}