#include "memory.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

//sets every byte in memory to 0x00
void reset_memory(struct Memory *mem){
    int i;
    for (i=0; i < DATA; i++){
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
uint8_t *get_memory_address_pointer(struct Memory *mem, uint16_t address){
    if (address < 0x0100)
        return mem->zero_page+address;
    else if (address < 0x0200)
        return mem->stack+(address-0x0100);
    else if (address > 0xFFF9)
        return mem->last_six+(address-0xFFF9);
    else
        return mem->data+(address-0x0200);
}

//reads a byte from memory via get_memory_address_pointer
uint8_t read_from_memory(struct Memory *mem, uint16_t address){
    uint8_t *pointer_to_address = get_memory_address_pointer(mem, address);
    return *pointer_to_address;
}

//reads a byte from memory via get_memory_address_pointer
void write_to_memory(struct Memory *mem, uint16_t address, uint8_t data){
    uint8_t *pointer_to_adress = get_memory_address_pointer(mem, address);
    *pointer_to_adress = data;
    return;
}

/*test
int main(){
    struct Memory mem;
    reset_memory(&mem);

    uint16_t arr[4] = {0xFFFA, 0x00FF, 0x100, 0x1401, 0x120};
    int i;

    write_to_memory(&mem, 0xFFFA, 0x10);
    write_to_memory(&mem, 0x00FF, 0x01);
    write_to_memory(&mem, 0x100, 0x40);
    write_to_memory(&mem, 0x1401, 0x12);

    for (i=0; i < 5; i++)
        printf("\n%x\n", read_from_memory(&mem, arr[i]));

    return 0;
}*/