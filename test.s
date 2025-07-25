/*
Instructions Not In ASMParse/

8XY0 - Set VX to value of VY -                                mov VX, VY
8XY1 - Set VX to Binary OR of VX and VY  -                    r.or VX, VY
8XY2 - Set VX to Binary AND of VX and VY -                    r.and VX, VY
8XY3 - Set VX to Logical XOR of VX and VY -                   r.xor VX, VY
8XY4 - Set VX to value of VX + value of VY -                  r.add VX, VY
8XY5 - Set VX to value of VX - value of VY -                  r.lsub VX, VY
8XY7 - Set VX to value of VY - value of VX -                  r.rsub VX, VY
8XY6 - Put value of VY into VX and bitshift 1 to the right -  r.bsr VX, VY
8XYE - Put value of VY into VX and bitshift 1 to the left -   r.bsl VX, VY

EX9E - Increment PC x2 if key in VX is pressed      - in.p VX
EXA1 - Increment PC x2 if key in VX is not pressed  - in.np VX

FX07 - Set VX to value of Delay Timer - tm.gd VX
FX15 - Set Delay timer to value in VX - tm.sd VX
FX18 - Set Sound timer to value in VX - tm.ss VX
FX1E - Add value of VX to I           - idxadd VX
FX0A - Blocking Get Key, store key pressed in VX - gkey VX
FX33 - Take number in VX, convert it to 3 Decimal Digits, and store it in RAM at Address in I - bcd VX


CUSTOM
DXF0 - Delay for value in VX seconds  - del VX
 */