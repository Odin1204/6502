; a program to divide 0xFA by 0x0F and store the result in 0x0000 and the remainder in 0x00001

init:
.org $8000
 LDA #$FA
 LDX #$F
 STX $15
 LDX #$0
loop:
 CMP $15
 BCC store
 SBC $15
 INX
 JMP loop

store:
 STX $0
 STA $1
