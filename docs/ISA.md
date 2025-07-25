# Wills CHIP-8 ISA

| ASM Prototype | Binary | Description                                                           |
|---------------|--------|-----------------------------------------------------------------------|
| imov VX, 0xNN | 6XNN   | Set VX to NN |
| iadd VX, 0xNN | 7XNN   | Add NN to VX |
| setidx 0xNNN  | ANNN   | Set I to NNN |
| cls           | 00E0   | Clear Screen |
| drw VX, VY, 0xN | DXYN   | Draw N Pixels tall, sprite from I at Horizontal X coord in VX, and Vertical Y coord at VY |
| ichar VX      | FX29   | Set I to address of Char Index in VX |
| rand VX, 0xNN | CXNN   | Get random number, Binary AND it with NN and store that in VX |
| jmp 0xNNN     | 1NNN   | Set PC to NNN |
| ret           | 00EE   | Return to and pop Stack[SP] |
| call 0xNNN    | 2NNN   | Push PC to Stack[SP] and Set PC to NNN |
| ocall 0xNNN   | BNNN   | Set PC to V0 + NNN |
| ipc.ie VX, 0xNN | 3XNN   | Increment PC x2 if VX == NN |
| ipc.ine VX, 0xNN | 4XNN  | Increment PC x2 if VX != NN |
| ipc.e VX, VY  | 5XY0   | Increment PC x2 if VX == VY |
| ipc.ne VX, VY | 9XY0   | Increment PC x2 if VX != VY |

| pusha         | FX55   | Push All Registers to RAM at value of I |
| popa          | FX65   | Pop All Registers to RAM from value of I |

ALl numbers are hex



