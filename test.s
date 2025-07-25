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

 */