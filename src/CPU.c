//===------- CPU.c - Main CPU Loop - C ----------------------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#include "common.h"
#include "Display.h"
#include "state.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_ADDRESS 0x200

void RunCPU(CHIP_State* state, EmuState* emstate, char exec[]){
    state->PC = 0;
    while (!emstate->InitializedDisplay) {
        NSLP(200000);
    }
    
    while (1) {
        WPollInputEvents(emstate);
        uint16_t CurrInst = (state->RAM[EXEC_OFFSET + state->PC] << 8) | state->RAM[EXEC_OFFSET + state->PC + 1];
        bool jamp = false;

        uint8_t op     = (CurrInst & 0xF000) >> 12;
        uint8_t x      = (CurrInst & 0x0F00) >> 8;
        uint8_t y      = (CurrInst & 0x00F0) >> 4;
        uint8_t n      = (CurrInst & 0x000F);
        uint8_t nn     = (CurrInst & 0x00FF);
        uint16_t nnn   = (CurrInst & 0x0FFF);

            dprint("Fetched Instruction %04x\n", CurrInst);
            if (CurrInst == 0x00E0){ // 00E0 - Clear Screen
                ClearDisplay(state);
            } else if (op == 1){ // 1NNN - Set PC to NNN
                state->PC = nnn;
                jamp = true;
                continue;
            } else if (op == 0x6){ // 6XNN - Set VX to NN
                uint8_t regnum = x;
                uint8_t regval = nn;
                state->V[regnum] = regval;
            } else if (op == 7){ // 7XNN - Add NN to VX 
                uint8_t regnum = x;
                uint8_t regval = nn;
                state->V[regnum] += regval;
            } else if (op == 0xA){ // ANNN - Set I to NNN 
                state->I = nnn;
            } else if (op == 0xD && nn == 0xF0){
                dprint("Pausing for %x secconds\n", state->V[x]);
                SSLP(state->V[x]);
            } else if (op == 0xD){ // DXYN - Draw N Pixels tall sprite from I at Horizontal X coord in VX, and Vertical Y coord at VY
                uint8_t height = n;
                DrawSprite(state->V[x], state->V[y], height, state);
            } else if (op == 0xF && nn == 0x29){ // FX29 - Set I to address of Char Index in VX 
                uint16_t fontdex = state->V[x];
                state->I = 0x300 + fontdex * 5;
                DumpState(state);
                dprint("FX29 on V[%d] = %d, I = 0x%X\n", x, fontdex, state->I);
            } else if (CurrInst == 0x00EE){ // 00EE - Return to and pop Stack[SP]
                if (state->Stack[0] > 0){
                    memcpy(&state->PC, &state->Stack[--state->SP], sizeof(state->PC));
                    jamp = true;
                    continue;
                }
            } else if (op == 0x2){ // 2NNN - Push PC to Stack[SP] and Set PC to NNN 
                memcpy(&state->Stack[state->SP++], &state->PC, sizeof(state->PC));
                state->PC = nnn;
                jamp = true;
                continue;
            } else if (op == 0x3){ // 3XNN - Increment PC if VX == NN 
                if (state->V[x] == nn) {
                    state->PC += 2;
                    jamp = true;
                    #ifdef DBG
                    printf("True");
                    DumpState(state);
                    #endif
                } 
                #ifdef DBG
                else {
                    printf("False");
                    DumpState(state);
                }
                #endif
            } else if (op == 0x4){ // 4XNN - Increment PC if VX != NN 
                if (state->V[x] != nn) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (op == 0x5 && n == 0x0){ // 5XY0 - Increment PC if VX == VY 
                if (state->V[x] == state->V[y]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (op == 0x9 && n == 0x0){ // 9XY0 - Increment PC if VX != VY
                if (state->V[x] != state->V[y]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (op == 0x8){
                char subinst = n;
                if (subinst == 0x0){ // 8XY0 - Set VX to value of VY
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                } else if (subinst == 0x1){ // 8XY1 - Set VX to Binary OR of VX and VY
                    uint8_t ord = state->V[x] | state->V[y];
                    memcpy(&state->V[x], &ord, sizeof(ord));
                } else if (subinst == 0x2){ // 8XY2 - Set VX to Binary AND of VX and VY
                    uint8_t andd = state->V[x] & state->V[y];
                    memcpy(&state->V[x], &andd, sizeof(andd));
                } else if (subinst == 0x3){ // 8XY3 - Set VX to Logical XOR of VX and VY 
                    uint8_t xord = state->V[x] ^ state->V[y];
                    memcpy(&state->V[x], &xord, sizeof(xord));
                } else if (subinst == 0x4){ // 8XY4 - Set VX to value of VX + value of VY 
                    uint8_t addd = state->V[x] + state->V[y];
                    memcpy(&state->V[x], &addd, sizeof(addd));
                } else if (subinst == 0x5){ // 8XY5 - Set VX to value of VX - value of VY 
                    uint8_t subd = state->V[x] - state->V[y];
                    memcpy(&state->V[x], &subd, sizeof(subd));
                } else if (subinst == 0x7){ // 8XY7 - Set VX to value of VY - value of VX 
                    uint8_t subd = state->V[y] - state->V[x];
                    memcpy(&state->V[x], &subd, sizeof(subd));      
                } else if (subinst == 0x6){ // 8XY6 - Put value of VY into VX and bitshift 1 to the right
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                    state->V[x] = state->V[x] >> 1;
                } else if (subinst == 0xE){ // 8XYE - Put value of VY into VX and bitshift 1 to the left
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                    state->V[x] = state->V[x] << 1;
                }
            } else if (op == 0xB){ // BNNN - Set PC to V0 + NNN
                state->PC = nnn + state->V[0];
                jamp = true;
                continue;
            } else if (op == 0xC){ // CXNN - Get random number, Binary AND it with NN and store that in VX
                uint8_t rando = rand();
                uint8_t randod = rando & nn;
                memcpy(&state->V[x], &randod, sizeof(randod));
            } else if (op == 0xE && nn == 0x9E){ // EX9E - Increment PC if key in VX is pressed
                if (emstate->keypad[state->V[x]]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (op == 0xE && nn == 0xA1){ // EXA1 - Increment PC if key in VX is not pressed
                if (!emstate->keypad[state->V[x]]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (op == 0xF){
                if (nn == 0x07){ // FX07 - Set VX to value of Delay Timer
                    memcpy(&state->V[x], &state->DelayTimer, sizeof(state->DelayTimer));
                } else if (nn == 0x15){ // FX15 - Set Delay timer to value in VX
                    memcpy(&state->DelayTimer, &state->V[x], sizeof(state->V[x]));
                } else if (nn == 0x18){ // FX18 - Set Sound timer to value in VX
                    memcpy(&state->SoundTimer, &state->V[x], sizeof(state->V[x]));
                } else if (nn == 0x1E){ // FX1E - Add value of VX to I
                    state->I += state->V[x];
                } else if (nn == 0x0A){ // FX0A - Blocking Get Key, store key pressed in VX
                    dprint("Waiting for key\n");
                    while (!emstate->IsKeyPressed){
                        if (state->DelayTimer > 0) state->DelayTimer--;
                        if (state->SoundTimer > 0 && !IsSoundPlaying(tone)) {
                            PlaySound(tone);
                            state->SoundTimer--;
                        }
                        NSLP(16667);
                        #pragma omp parallel
                        {
                            WPollInputEvents(emstate);
                        }
                        printf("Polling for key... Current: %d\n", atomic_load(&emstate->IsKeyPressed));
                        if (emstate->IsKeyPressed){
                            break;
                        }
                    }
                    memcpy(&state->V[x], &emstate->keypressed, sizeof(emstate->keypressed));
                    dprint("Got Key %x\n", state->V[x]);
                } else if (nn == 0x33){ // FX33 - Take number in VX, convert it to 3 Decimal Digits, and store it in RAM at Address in I
                    uint8_t val = state->V[x];
                    state->RAM[state->I + USR_RAM_OFFSET] = val / 100;
                    state->RAM[(state->I + USR_RAM_OFFSET) + 1] = (val / 10) % 10;
                    state->RAM[(state->I + USR_RAM_OFFSET) + 2] = val % 10;
                } else if (nn == 0x55){ // FX55 - Push All Registers to RAM at value of I
                    PushAllRegs(state, emstate);
                } else if (nn == 0x65){ // FX65 - Pop All Registers to RAM from value of I
                    PopAllRegs(state, emstate);
                }
            } else if (op == 0x0 && x == 0x1){
                FlipPixel(state->V[x], state->V[y], state);
            }
        if (!jamp) state->PC++;
        if (state->DelayTimer > 0) state->DelayTimer--;
        if (state->SoundTimer > 0 && !IsSoundPlaying(tone)) {
            PlaySound(tone);
            state->SoundTimer--;
        }
        NSLP(16667);
    }
}