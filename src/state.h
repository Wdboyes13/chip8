//===------- state.h - Provides state-related things - C Header ----------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdio.h>

#define KEYNPRESSED -1
#define NUMKEYS 16
#define USR_RAM_OFFSET (0x300 + 200)

typedef struct CHIP_State {
    uint8_t RAM[4096 + (200 + 0x300)];     // Memory: CHIP-8 has direct access to up to 4 kilobytes of RAM
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
    volatile int CursorX;
    volatile int CursorY;
    atomic_bool keypad[NUMKEYS];
    atomic_bool IsKeyPressed;
    atomic_uint_fast8_t keypressed;
} EmuState;


#ifdef DBG
  #define dprint(...) printf(__VA_ARGS__)
#else
  #define dprint(...) ((void)0)
#endif

static void DumpState(CHIP_State* state){
    dprint("PC: %x\n", state->PC);
    dprint("SP: %x\n", state->SP);
    dprint("I: %x\n", state->I);
    for (int i = 0; i < 16; i++){
        dprint("Stack[%d]: %x\n", i, state->Stack[i]);
        dprint("V[%d]: %x\n", i, state->V[i]);
    }
    dprint("DelayTimer: %x\n", state->DelayTimer);
    dprint("SoundTimer: %x\n", state->SoundTimer);
}