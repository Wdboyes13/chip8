#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct CHIP_State {
    uint8_t RAM[4096];     // Memory: CHIP-8 has direct access to up to 4 kilobytes of RAM
    uint16_t PC;           // A program counter, often called just “PC”, which points at the current instruction in memory
    uint16_t SP;
    uint16_t I;            // One 16-bit index register called “I” which is used to point at locations in memory
    uint16_t Stack[16];    // A stack for 16-bit addresses, which is used to call subroutines/functions and return from them
    uint8_t DelayTimer;    // An 8-bit delay timer which is decremented at a rate of 60 Hz (60 times per second) until it reaches 0
    uint8_t SoundTimer;    // An 8-bit sound timer which functions like the delay timer, but which also gives off a beeping sound as long as it’s not 0
    uint8_t V[16]; // 16 8-bit (one byte) general-purpose variable registers numbered 0 through F hexadecimal, ie. 0 through 15 in decimal, called V0 through VF
                              // VF is also used as a flag register; many instructions will set it to either 1 or 0 based on some rule, for example using it as a carry flag
    bool Display[64][32];  // Display: 64 x 32 pixels (or 128 x 64 for SUPER-CHIP) monochrome, ie. black or white
} CHIP_State;

typedef struct EmuState {
    bool AllocatedState;
    bool InitializedDisplay;
    int CursorX;
    int CursorY;
} EmuState;

