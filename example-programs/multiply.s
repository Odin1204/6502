; program to multiply 0x40 and 0x0A and store the result in 0x0000 and 0x0001

init:
.org $8000
 LDA #$40
 LDX #$A
 BEQ done
 STA $15

loop:
 ADC $15

 BCC CHECK

 PHA
 LDA #0
 ADC $1
 STA $1
 PLA
 JMP CHECK


CHECK:
 DEX
 DEX 
 BEQ done
 INX
 JMP loop

done:
 STA $0