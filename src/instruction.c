#define INTERNAL_CPU_ACCESS

#include "instructions.h"
#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*Address modes declarations*/

static uint8_t IMP(void);
static uint8_t IMM(void);
static uint8_t ZP0(void);
static uint8_t ZPX(void);
static uint8_t ZPY(void);
static uint8_t ABS(void);
static uint8_t ABX(void);
static uint8_t ABY(void);
static uint8_t IND(void);
static uint8_t IZX(void);
static uint8_t IZY(void);
static uint8_t REL(void);

/*Operation declarations*/

static uint8_t XXX(void);
static uint8_t LDA(void);
static uint8_t LDX(void);
static uint8_t LDY(void);
static uint8_t BRK(void);
static uint8_t BPL(void);
static uint8_t JSR(void);
static uint8_t BMI(void);
static uint8_t RTI(void);
static uint8_t BVC(void);
static uint8_t RTS(void);
static uint8_t BVS(void);
static uint8_t NOP(void);
static uint8_t BCC(void);
static uint8_t BCS(void);
static uint8_t BNE(void);
static uint8_t CPX(void);
static uint8_t CPY(void);
static uint8_t BEQ(void);
static uint8_t ORA(void);
static uint8_t AND(void);
static uint8_t EOR(void);
static uint8_t BIT(void);
static uint8_t ADC(void);
static uint8_t STA(void);
static uint8_t STX(void);
static uint8_t STY(void);
static uint8_t CMP(void);
static uint8_t SBC(void);
static uint8_t ASL(void);
static uint8_t ROL(void);
static uint8_t LSR(void);
static uint8_t ROR(void);
static uint8_t DEC(void);
static uint8_t DEX(void);
static uint8_t DEY(void);
static uint8_t INC(void);
static uint8_t INX(void);
static uint8_t INY(void);
static uint8_t PHP(void);
static uint8_t SEC(void);
static uint8_t CLC(void);
static uint8_t CLI(void);
static uint8_t PLP(void);
static uint8_t PLA(void);
static uint8_t PHA(void);
static uint8_t SEI(void);
static uint8_t TYA(void);
static uint8_t CLV(void);
static uint8_t CLD(void);
static uint8_t SED(void);
static uint8_t TXA(void);
static uint8_t TXS(void);
static uint8_t TAX(void);
static uint8_t TAY(void);
static uint8_t TSX(void);
static uint8_t JMP(void);

/*lookup table of opcodes*/
struct instruction lookup[256] = {
    {"BRK", &BRK, &IMM, 7}, {"ORA", &ORA, &IZX, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3}, {"ORA", &ORA, &ZP0, 3},
    {"ASL", &ASL, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"PHP", &PHP, &IMP, 3},
    {"ORA", &ORA, &IMM, 2}, {"ASL", &ASL, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"???", &NOP, &IMP, 4}, {"ORA", &ORA, &ABS, 4}, {"ASL", &ASL, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BPL", &BPL, &REL, 2}, {"ORA", &ORA, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"ORA", &ORA, &ZPX, 4}, {"ASL", &ASL, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"CLC", &CLC, &IMP, 2}, {"ORA", &ORA, &ABY, 4}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"ORA", &ORA, &ABX, 4},
    {"ASL", &ASL, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"JSR", &JSR, &ABS, 6},
    {"AND", &AND, &IZX, 6}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"BIT", &BIT, &ZP0, 3}, {"AND", &AND, &ZP0, 3}, {"ROL", &ROL, &ZP0, 5},
    {"???", &XXX, &IMP, 5}, {"PLP", &PLP, &IMP, 4}, {"AND", &AND, &IMM, 2},
    {"ROL", &ROL, &IMP, 2}, {"???", &XXX, &IMP, 2}, {"BIT", &BIT, &ABS, 4},
    {"AND", &AND, &ABS, 4}, {"ROL", &ROL, &ABS, 6}, {"???", &XXX, &IMP, 6},
    {"BMI", &BMI, &REL, 2}, {"AND", &AND, &IZY, 5}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4}, {"AND", &AND, &ZPX, 4},
    {"ROL", &ROL, &ZPX, 6}, {"???", &XXX, &IMP, 6}, {"SEC", &SEC, &IMP, 2},
    {"AND", &AND, &ABY, 4}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7},
    {"???", &NOP, &IMP, 4}, {"AND", &AND, &ABX, 4}, {"ROL", &ROL, &ABX, 7},
    {"???", &XXX, &IMP, 7}, {"RTI", &RTI, &IMP, 6}, {"EOR", &EOR, &IZX, 6},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3},
    {"EOR", &EOR, &ZP0, 3}, {"LSR", &LSR, &ZP0, 5}, {"???", &XXX, &IMP, 5},
    {"PHA", &PHA, &IMP, 3}, {"EOR", &EOR, &IMM, 2}, {"LSR", &LSR, &IMP, 2},
    {"???", &XXX, &IMP, 2}, {"JMP", &JMP, &ABS, 3}, {"EOR", &EOR, &ABS, 4},
    {"LSR", &LSR, &ABS, 6}, {"???", &XXX, &IMP, 6}, {"BVC", &BVC, &REL, 2},
    {"EOR", &EOR, &IZY, 5}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"???", &NOP, &IMP, 4}, {"EOR", &EOR, &ZPX, 4}, {"LSR", &LSR, &ZPX, 6},
    {"???", &XXX, &IMP, 6}, {"CLI", &CLI, &IMP, 2}, {"EOR", &EOR, &ABY, 4},
    {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4},
    {"EOR", &EOR, &ABX, 4}, {"LSR", &LSR, &ABX, 7}, {"???", &XXX, &IMP, 7},
    {"RTS", &RTS, &IMP, 6}, {"ADC", &ADC, &IZX, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 3}, {"ADC", &ADC, &ZP0, 3},
    {"ROR", &ROR, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"PLA", &PLA, &IMP, 4},
    {"ADC", &ADC, &IMM, 2}, {"ROR", &ROR, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"JMP", &JMP, &IND, 5}, {"ADC", &ADC, &ABS, 4}, {"ROR", &ROR, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BVS", &BVS, &REL, 2}, {"ADC", &ADC, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"ADC", &ADC, &ZPX, 4}, {"ROR", &ROR, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"SEI", &SEI, &IMP, 2}, {"ADC", &ADC, &ABY, 4}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"ADC", &ADC, &ABX, 4},
    {"ROR", &ROR, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 2},
    {"STA", &STA, &IZX, 6}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 6},
    {"STY", &STY, &ZP0, 3}, {"STA", &STA, &ZP0, 3}, {"STX", &STX, &ZP0, 3},
    {"???", &XXX, &IMP, 3}, {"DEY", &DEY, &IMP, 2}, {"???", &NOP, &IMP, 2},
    {"TXA", &TXA, &IMP, 2}, {"???", &XXX, &IMP, 2}, {"STY", &STY, &ABS, 4},
    {"STA", &STA, &ABS, 4}, {"STX", &STX, &ABS, 4}, {"???", &XXX, &IMP, 4},
    {"BCC", &BCC, &REL, 2}, {"STA", &STA, &IZY, 6}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 6}, {"STY", &STY, &ZPX, 4}, {"STA", &STA, &ZPX, 4},
    {"STX", &STX, &ZPY, 4}, {"???", &XXX, &IMP, 4}, {"TYA", &TYA, &IMP, 2},
    {"STA", &STA, &ABY, 5}, {"TXS", &TXS, &IMP, 2}, {"???", &XXX, &IMP, 5},
    {"???", &NOP, &IMP, 5}, {"STA", &STA, &ABX, 5}, {"???", &XXX, &IMP, 5},
    {"???", &XXX, &IMP, 5}, {"LDY", &LDY, &IMM, 2}, {"LDA", &LDA, &IZX, 6},
    {"LDX", &LDX, &IMM, 2}, {"???", &XXX, &IMP, 6}, {"LDY", &LDY, &ZP0, 3},
    {"LDA", &LDA, &ZP0, 3}, {"LDX", &LDX, &ZP0, 3}, {"???", &XXX, &IMP, 3},
    {"TAY", &TAY, &IMP, 2}, {"LDA", &LDA, &IMM, 2}, {"TAX", &TAX, &IMP, 2},
    {"???", &XXX, &IMP, 2}, {"LDY", &LDY, &ABS, 4}, {"LDA", &LDA, &ABS, 4},
    {"LDX", &LDX, &ABS, 4}, {"???", &XXX, &IMP, 4}, {"BCS", &BCS, &REL, 2},
    {"LDA", &LDA, &IZY, 5}, {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 5},
    {"LDY", &LDY, &ZPX, 4}, {"LDA", &LDA, &ZPX, 4}, {"LDX", &LDX, &ZPY, 4},
    {"???", &XXX, &IMP, 4}, {"CLV", &CLV, &IMP, 2}, {"LDA", &LDA, &ABY, 4},
    {"TSX", &TSX, &IMP, 2}, {"???", &XXX, &IMP, 4}, {"LDY", &LDY, &ABX, 4},
    {"LDA", &LDA, &ABX, 4}, {"LDX", &LDX, &ABY, 4}, {"???", &XXX, &IMP, 4},
    {"CPY", &CPY, &IMM, 2}, {"CMP", &CMP, &IZX, 6}, {"???", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"CPY", &CPY, &ZP0, 3}, {"CMP", &CMP, &ZP0, 3},
    {"DEC", &DEC, &ZP0, 5}, {"???", &XXX, &IMP, 5}, {"INY", &INY, &IMP, 2},
    {"CMP", &CMP, &IMM, 2}, {"DEX", &DEX, &IMP, 2}, {"???", &XXX, &IMP, 2},
    {"CPY", &CPY, &ABS, 4}, {"CMP", &CMP, &ABS, 4}, {"DEC", &DEC, &ABS, 6},
    {"???", &XXX, &IMP, 6}, {"BNE", &BNE, &REL, 2}, {"CMP", &CMP, &IZY, 5},
    {"???", &XXX, &IMP, 2}, {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4},
    {"CMP", &CMP, &ZPX, 4}, {"DEC", &DEC, &ZPX, 6}, {"???", &XXX, &IMP, 6},
    {"CLD", &CLD, &IMP, 2}, {"CMP", &CMP, &ABY, 4}, {"NOP", &NOP, &IMP, 2},
    {"???", &XXX, &IMP, 7}, {"???", &NOP, &IMP, 4}, {"CMP", &CMP, &ABX, 4},
    {"DEC", &DEC, &ABX, 7}, {"???", &XXX, &IMP, 7}, {"CPX", &CPX, &IMM, 2},
    {"SBC", &SBC, &IZX, 6}, {"???", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 8},
    {"CPX", &CPX, &ZP0, 3}, {"SBC", &SBC, &ZP0, 3}, {"INC", &INC, &ZP0, 5},
    {"???", &XXX, &IMP, 5}, {"INX", &INX, &IMP, 2}, {"SBC", &SBC, &IMM, 2},
    {"NOP", &NOP, &IMP, 2}, {"???", &SBC, &IMP, 2}, {"CPX", &CPX, &ABS, 4},
    {"SBC", &SBC, &ABS, 4}, {"INC", &INC, &ABS, 6}, {"???", &XXX, &IMP, 6},
    {"BEQ", &BEQ, &REL, 2}, {"SBC", &SBC, &IZY, 5}, {"???", &XXX, &IMP, 2},
    {"???", &XXX, &IMP, 8}, {"???", &NOP, &IMP, 4}, {"SBC", &SBC, &ZPX, 4},
    {"INC", &INC, &ZPX, 6}, {"???", &XXX, &IMP, 6}, {"SED", &SED, &IMP, 2},
    {"SBC", &SBC, &ABY, 4}, {"NOP", &NOP, &IMP, 2}, {"???", &XXX, &IMP, 7},
    {"???", &NOP, &IMP, 4}, {"SBC", &SBC, &ABX, 4}, {"INC", &INC, &ABX, 7},
    {"???", &XXX, &IMP, 7},
};

//initialise the emulator state variables
struct emulator_state state;


// sets all emulator state vars to 0
static void reset_emulaor_state(){
    state.addr_abs = 0x0;
    state.addr_rel = 0x0;
    state.opcode = 0x0;
    state.fetched = 0x0;
}

//sets a specific bit in the flag register to 0 or 1
static void set_flag(uint8_t flag, uint8_t val){
    if (val)
        set_status_flag(flag, 1);
    else
        set_status_flag(flag, 0);
}

//gets a specific bit in the flag register
static uint8_t get_flag(uint8_t flag){
    return extract_flag(flag);
}

//fetches address mode and stores it in the state.fetch variable
static void fetch(void){
    if (lookup[state.opcode].mode != &IMP)
        state.fetched = cpu_read(state.addr_abs);
    
    return state.fetched;
}

/*stores the opcode in the state.opcode variable, sets the cycles variable of the cpu.c file to the 
  corresponding cycles, executes the addressing mode and operation. If needed it also adds an additional cycle*/ 
void execute_instruction(uint8_t op, uint8_t *cycles){
    uint8_t additional_cycle1, additional_cycle2;
    
    state.opcode = op;
    
    *cycles = lookup[op].cycles;

    additional_cycle1 = (*(lookup[op].mode))();
    additional_cycle2 = (*(lookup[op].operation))();

    *cycles += additional_cycle1 & additional_cycle2;
}


//Addressing modes


//Implicit: For instruction where the datat is implied by the function of the instruction or is the accumulator
uint8_t IMP(void){
    state.fetched = cpu.accumulator;  
    
    return 0;
}

//Immediate: The data is specified by the next byte in the program
uint8_t IMM(void){
    state.addr_abs = cpu.program_counter++;

    return 0;
}

//Zero Page: Uses only the Data from the first page in memory specified by an 8-bit operand. 
uint8_t ZP0(void){
    state.addr_abs = (cpu_read(cpu.program_counter++) & 0x00FF);

    return 0;
}

/*Zero Page with X offset: Offsets the specified 8-bit operand by the content of the X register.
  If the zero page is crossed it wraps around. So if the operand is 0xFF and X is 0x02 the address will be 0x01.*/
uint8_t ZPX(void){
    state.addr_abs = ((cpu_read(cpu.program_counter++) + cpu.x) & 0x00FF);

    return 0;
}

//Zero Page with Y offset: Same as ZPX but with the Y register.
uint8_t ZPY(void){
    state.addr_abs = ((cpu_read(cpu.program_counter++) + cpu.y) & 0x00FF);

    return 0;
}

/*Relative: Only for Branch instructions. 
  It can only jump within the range of -127 to 128 relative to the program counter.
  If the 7th bit is 0, so the number is signed, the high byte is set to 0xFF so arithmatic will work.*/
uint8_t REL(void){
    state.addr_rel = (cpu_read(cpu.program_counter));
    if (state.addr_rel | 0x80)
        state.addr_rel |= 0xFF00;

    return 0;
}

//Absolute: Operand specifies an absolute 16-bit address
uint8_t ABS(void){
    uint16_t low = cpu_read(cpu.program_counter++);
    uint16_t high = (cpu_read(cpu.program_counter++) << 8);

    state.addr_abs = high | low;

    return 0;
}

/*Absolute with X offset: Offsets the absolute address by the contents of the X register.
  If a page is crossed it may need an additional clock cycle.*/
uint8_t ABX(void){
    uint16_t low = cpu_read(cpu.program_counter++);
    uint16_t high = (cpu_read(cpu.program_counter++) << 8);

    state.addr_abs = (high | low) + cpu.x;

    if (high != (state.addr_abs & 0xFF00))
        return 1;
    else
        return 0;
}

//Absolute with Y offset: Same as ABX but with the Y Register
uint8_t ABY(void){
    uint16_t low = cpu_read(cpu.program_counter++);
    uint16_t high = (cpu_read(cpu.program_counter++) << 8);

    state.addr_abs = (high | low) + cpu.y;

    if (high != (state.addr_abs & 0xFF00))
        return 1;
    else
        return 0;
}

/*Indirect: The Operant is a pointer to the absolute address.
  There is a bug in the harware, that if a page would be crossed with the increase of the pointer
  after the low byte has been read, the pointer wraps around on the current page and the high byte
  is the first elemt of the current page.*/
uint8_t IND(void){
    uint16_t low_ptr = cpu_read(cpu.program_counter++);
    uint16_t high_ptr = (cpu_read(cpu.program_counter++) << 8);

    uint16_t ptr = high_ptr | low_ptr;

    uint16_t low = cpu_read(ptr);
    
    uint16_t high;

    //normal
    if (low_ptr != 0x00FF)
        high = (cpu_read(++ptr) << 8);
    else //bug
        high = (cpu_read(ptr & 0xFF00) << 8);

    state.addr_abs = high | low;

    return 0; 
}

/*Indirect Zero Page with X offset: Operand is an 8-bit pointer to somewhere in the first page,
  offsets it by x and retrives the 16-bit address. If the zero page would be crossed, 
  when adding X or increasing it, it wraps aroud.*/
uint8_t IZX(void){
    uint16_t ptr = ((cpu_read(cpu.program_counter++) + cpu.x) & 0x00FF);

    uint16_t low = cpu_read(ptr++);
    uint16_t high = (cpu_read(ptr & 0x00FF) << 8);

    state.addr_abs = high | low;

    return 0;
}

/*Indirect Zero Page with Y offset: Operand is an 8-bit pointer to somewhere in the first page,
  retrives a 16-bit address and offsets the address by Y. When the zero page would be crossed when 
  the pointer is increased it wraps around. When a page is crossed when adding Y an additional clock cycle 
  may be required.*/
uint8_t IZY(void){
    uint16_t ptr = (cpu_read(cpu.program_counter++) & 0x00FF);

    uint16_t low = cpu_read(ptr++);
    uint16_t high = (cpu_read(ptr & 0x00FF) << 8);

    state.addr_abs = (high | low) + cpu.y;

    if (high != (state.addr_abs & 0xFF00))
        return 1;
    else
        return 0;
}