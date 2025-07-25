# Wills CHIP-8 ISA

## Drawing
| ASM Instruction | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| cls           | 00E0   | Clear Screen |
| drw VX, VY, 0xN | DXYN   | Draw N Pixels tall, sprite from I at Horizontal X coord in VX, and Vertical Y coord at VY |
| ichar VX      | FX29   | Set I to address of Char Index in VX |

## Memory
| ASM Instruction | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| idxadd VX     | FX1E   | Add value of VX to I |
| bcd VX        | FX33   | Take number in VX, convert it to 3 Decimal Digits, and store it in RAM at Address in I |
| pusha         | FX55   | Push All Registers to RAM at value of I |
| popa          | FX65   | Pop All Registers to RAM from value of I |
| imov VX, 0xNN | 6XNN   | Set VX to NN |
| iadd VX, 0xNN | 7XNN   | Add NN to VX |
| setidx 0xNNN  | ANNN   | Set I to NNN |

## Flow Control
| ASM Instruction | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| jmp 0xNNN     | 1NNN   | Set PC to NNN |
| ret           | 00EE   | Return to and pop Stack[SP] |
| call 0xNNN    | 2NNN   | Push PC to Stack[SP] and Set PC to NNN |
| ocall 0xNNN   | BNNN   | Set PC to V0 + NNN |
| ipc.ie VX, 0xNN | 3XNN   | Increment PC x2 if VX == NN |
| ipc.ine VX, 0xNN | 4XNN  | Increment PC x2 if VX != NN |
| ipc.e VX, VY  | 5XY0   | Increment PC x2 if VX == VY |
| ipc.ne VX, VY | 9XY0   | Increment PC x2 if VX != VY |
## Math
| ASM Instruction | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| mov VX, VY    | 8XY0   | Set VX to value of VY |
| r.or VX, VY   | 8XY1   | Set VX to Binary OR of VX and VY |
| r.and VX, VY  | 8XY2   | Set VX to Binary AND of VX and VY |
| r.xor VX, VY  | 8XY3   | Set VX to Logical XOR of VX and VY |
| r.add VX, VY  | 8XY4   | Set VX to value of VX + value of VY |
| r.lsub VX, VY | 8XY5   | Set VX to value of VX - value of VY |
| r.rsub VX, VY | 8XY7   | Set VX to value of VY - value of VX |
| r.bsr VX, VY  | 8XY6   | Put value of VY into VX and bitshift 1 to the right |
| r.bsl VX, VY  | 8XYE   | Put value of VY into VX and bitshift 1 to the left |
## Other
| ASM Instruction | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| rand VX, 0xNN | CXNN   | Get random number, Binary AND it with NN and store that in VX |
| tm.gd VX      | FX07   | Set VX to value of Delay Timer |
| tm.sd VX      | FX15   | Set Delay timer to value in VX |
| tm.ss VX      | FX18   | Set Sound timer to value in VX |
| gkey VX       | FX0A   | Blocking Get Key, store key pressed in VX |
| del VX        | DXF0   | Delay for value in VX seconds (Custom Instruction) |

ALL numbers are hex

