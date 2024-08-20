; program to calculate the fibonacci sequence of a number

init:
.org $8000
 LDX #17 ; the xth fibonacci number
 LDA #$1
 DEX
loop:
 BEQ store
 TAY
 ADC $10
 STY $10

 BCC no_carry
 JSR high_byte
 DEX
 JMP loop

no_carry:
 DEX
 JSR high_byte
 JMP loop

store:
 STA $0
 brk

high_byte:
 PHA
 LDA $1
 TAY
 ADC $11
 STY $11
 STA $1
 PLA
 RTS
