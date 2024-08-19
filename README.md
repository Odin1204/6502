# 6502 Emulator

An easy to understand Emulator for the mos 6502 written in C.

## How to compile and run

to compile the program simply type

` make `



In order to then run the program you need to have a binary for the 6502,
that you can assemble with any online 6502 assembler. (I used [this one](https://www.masswerk.at/6502/assembler.html))

Then simply run

` ./6502_EMULATOR any_program.bin `

To clean it up afterwards just run

` make clean `

## Coding

This Project is split in multiple files in order to make it easier to understand and have multiple layers of abstraction or emulate the CPU more faithfully. 
The components are:
+ **CPU**: The heart of the project. It can read and write to the Bus and has the clock function.
+ **Instructions**: An extension of the cpu. Here is where the instructions will be executed. You very easily  
                        just put it in the cpu.c file.
+ **Bus**: An abstraction layer between cpu and memory. It gives the possibility to easily add more components.
+ **Memory**: 64KB of memory that can be read an written to. It is split into the Zero Page, Stack, Data and    
                  last six.
+ **Main**: To load the program and start it and handle the *"clock logic"*

### LOGMODE
In the cpu.c, instructions.c and main.c files there LOGMODE to see what happened to the registers after every 
Instruction and to print the memory to a memdump.txt file after the program is done. 
I would suggest to leave it uncommented in the cpu and main file, since you won't really see much otherwise. 
In the instruction file it only tells you the Stack operations, the Name of instruction and the absolute address.

### TODO
- [ ] **main.c:** The way **main.c** handles the execution of programs is not ideal since it will ask if you want   
                  to continue after every Instruction.

## Acknowledgements

This project was made possible with the help of the following Resources:

- **[olcNes-CPU](https://github.com/OneLoneCoder/olcNES/tree/master/Part%232%20-%20CPU)**: an overall great 
            resource since it is higly commented and the videos help you understand it even better.
- **[f0lg0-6502](https://github.com/f0lg0/6502/tree/main)**: Especially helpful for the Opcode lookup matrix.
- **[6502.org](http://www.6502.org/users/obelisk/6502/index.html)**: Great breakdown of components, addressing 
modes and Instructions. 
