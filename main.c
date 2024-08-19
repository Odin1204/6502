#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./src/cpu.h"

#define LOGMODE

//total memory
#define MEM 0xFFFF
//memory without last six
#define MEM_W_O_L_6 0xFFF9


/*loads program into the specified program array and returns the size of it*/
int load_program(char *filename, uint8_t *program_array, uint16_t max_size){
    FILE *program = fopen(filename, "rb");

    if (!program){
        perror("failed to open file");
        return -1;
    }

    size_t bytes_read = fread(program_array, 1, max_size, program);

    if (bytes_read <= 0){
        perror("failed to read file");
        fclose(program);
        return -1;
    }

    if (bytes_read == max_size)
        printf("\nWARNING: Max size of program size has been reached! The program may be too big.");

    fclose(program);
    
    return bytes_read;
}

//iterates over program array and writes it into memory from a starting position
void write_program_to_memory(uint8_t *program, int length, uint16_t starting_position){
    uint16_t pp;
    uint16_t mp;

    for (pp = 0 ,mp = starting_position; pp<length; pp++, mp++)
        cpu_write(mp, program[pp]);

}

//Dumps memory in file
void memdump(){
    FILE *file = fopen("memdump.txt", "w");

    if (file == NULL){
        perror("failed to open file");
        return;
    }

    uint16_t i;
    for (i = 0; i < MEM; i++){
        if (i=0)
            fprintf(file, "Zero Page:\n");
        
        if (i=0x100)
            fprintf(file, "\nStack: \n");

        if (i=0x200)
            fprintf(file, "\nData: \n");
        
        if (!(i % 16))
            fprintf(file, "\n%x: %x ", i, cpu_read(i));
        else
            fprintf(file, "%x ", cpu_read(i));
    }
}

void can_continue(){
    char c;

    printf("Continue? y/n\n");
    c = getchar();
    getchar();

    if (c == 'y')
        return;
    else if (c == 'n'){

        #ifdef LOGMODE
        memdump();
        #endif
        
        exit(0);
    }
    else {
        printf("ERROR: unknown input -- continue %c\n", c);
        exit(1);
    }
}



int main(int argc, char *argv[]){

    cpu_reset();

    uint16_t max_program_size = MEM_W_O_L_6 - cpu.program_counter;
    uint8_t program_array[max_program_size];

    int program_length = load_program(argv[1], program_array, max_program_size);
    
    if (program_length == -1)
        return -1;
    
    write_program_to_memory(program_array, program_length, cpu.program_counter);

    //clock loop: will ask you if you want to continue after every instruction
    while (cpu.program_counter < MEM_W_O_L_6){
        clock();
        while(cycles)
            clock();
        can_continue();

    }
    

    return 0;
}