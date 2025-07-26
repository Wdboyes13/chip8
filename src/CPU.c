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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void RunCPU(CHIP_State* state, EmuState* emstate, char exec[]){
    int execlen = 1;
    state->PC = 0;
    while (!emstate->InitializedDisplay) {
        NSLP(200000);
    }
    char* line = strtok(exec, "\r\n");
    while (line != NULL) {
        WPollInputEvents(emstate);
        bool jamp = false;
        char CurrInst[5];

        if (sscanf(line, "%4s", CurrInst) == 1) {
            dprint("Fetched instruction: 0x%s\n", CurrInst);
            if (strcmp(CurrInst, "00E0") == 0){ // 00E0 - Clear Screen
                ClearDisplay(state);
            } else if (CurrInst[0] == '1'){ // 1NNN - Set PC to NNN
                const char* sub = CurrInst + 1;
                state->PC = (uint16_t)strtol(sub, NULL, 16);
                jamp = true;
                continue;
            } else if (CurrInst[0] == '6'){ // 6XNN - Set VX to NN
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                int regnum = (inst & 0x0F00) >> 8;
                int regval = inst & 0x00FF;
                state->V[regnum] = regval;
            } else if (CurrInst[0] == '7'){ // 7XNN - Add NN to VX 
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                int regnum = (inst & 0x0F00) >> 8;
                int regval = inst & 0x00FF;
                state->V[regnum] += regval;
            } else if (CurrInst[0] == 'A'){ // ANNN - Set I to NNN 
                const char* sub = CurrInst + 1;
                state->I = (uint16_t)strtol(sub, NULL, 16);
            } else if (CurrInst[0] == 'D' && CurrInst[2] == 'F' && CurrInst[3] == '0'){
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                dprint("Pausing for %x secconds\n", state->V[x]);
                SSLP(state->V[x]);
            } else if (CurrInst[0] == 'D'){ // DXYN - Draw N Pixels tall sprite from I at Horizontal X coord in VX, and Vertical Y coord at VY
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                uint8_t y = (inst & 0x00F0) >> 4;
                uint8_t height = inst & 0x000F;
                DrawSprite(state->V[x], state->V[y], height, state);
            } else if (CurrInst[0] == 'F' && CurrInst[2] == '2' && CurrInst[3] == '9'){ // FX29 - Set I to address of Char Index in VX 
                int x;
                sscanf(&CurrInst[1], "%1X", &x);
                uint16_t fontdex = state->V[x];
                state->I = 0x300 + fontdex * 5;

                DumpState(state);
                dprint("FX29 on V[%d] = %d, I = 0x%X\n", x, fontdex, state->I);
            } else if (strcmp(CurrInst, "00EE") == 0){ // 00EE - Return to and pop Stack[SP]
                if (state->Stack[0] > 0){
                    memcpy(&state->PC, &state->Stack[--state->SP], sizeof(state->PC));
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == '2'){ // 2NNN - Push PC to Stack[SP] and Set PC to NNN 
                memcpy(&state->Stack[state->SP++], &state->PC, sizeof(state->PC));
                const char* sub = CurrInst + 1;
                state->PC = (uint16_t)strtol(sub, NULL, 16);
                jamp = true;
                continue;
            } else if (CurrInst[0] == '3'){ // 3XNN - Increment PC if VX == NN 
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                int nn = inst & 0x00FF;
                if (state->V[x] == nn) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == '4'){ // 4XNN - Increment PC if VX != NN 
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                int nn = inst & 0x00FF;
                if (state->V[x] != nn) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == '5' && CurrInst[3] == '0'){ // 5XY0 - Increment PC if VX == VY 
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                uint8_t y = (inst & 0x00F0) >> 4;
                if (state->V[x] == state->V[y]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == '9' && CurrInst[3] == '0'){ // 9XY0 - Increment PC if VX != VY
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                uint8_t y = (inst & 0x00F0) >> 4;
                if (state->V[x] != state->V[y]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == '8'){
                char subinst = CurrInst[3];
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                uint8_t y = (inst & 0x00F0) >> 4;
                if (subinst == '0'){ // 8XY0 - Set VX to value of VY
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                } else if (subinst == '1'){ // 8XY1 - Set VX to Binary OR of VX and VY
                    uint8_t ord = state->V[x] | state->V[y];
                    memcpy(&state->V[x], &ord, sizeof(ord));
                } else if (subinst == '2'){ // 8XY2 - Set VX to Binary AND of VX and VY
                    uint8_t andd = state->V[x] & state->V[y];
                    memcpy(&state->V[x], &andd, sizeof(andd));
                } else if (subinst == '3'){ // 8XY3 - Set VX to Logical XOR of VX and VY 
                    uint8_t xord = state->V[x] ^ state->V[y];
                    memcpy(&state->V[x], &xord, sizeof(xord));
                } else if (subinst == '4'){ // 8XY4 - Set VX to value of VX + value of VY 
                    uint8_t addd = state->V[x] + state->V[y];
                    memcpy(&state->V[x], &addd, sizeof(addd));
                } else if (subinst == '5'){ // 8XY5 - Set VX to value of VX - value of VY 
                    uint8_t subd = state->V[x] - state->V[y];
                    memcpy(&state->V[x], &subd, sizeof(subd));
                } else if (subinst == '7'){ // 8XY7 - Set VX to value of VY - value of VX 
                    uint8_t subd = state->V[y] - state->V[x];
                    memcpy(&state->V[x], &subd, sizeof(subd));      
                } else if (subinst == '6'){ // 8XY6 - Put value of VY into VX and bitshift 1 to the right
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                    state->V[x] = state->V[x] >> 1;
                } else if (subinst == 'E'){ // 8XYE - Put value of VY into VX and bitshift 1 to the left
                    memcpy(&state->V[x], &state->V[y], sizeof(state->V[y]));
                    state->V[x] = state->V[x] << 1;
                }
            } else if (CurrInst[0] == 'B'){ // BNNN - Set PC to V0 + NNN
                const char* sub = CurrInst + 1;
                state->PC = ((uint16_t)strtol(sub, NULL, 16)) + state->V[0];
                jamp = true;
                continue;
            } else if (CurrInst[0] == 'C'){ // CXNN - Get random number, Binary AND it with NN and store that in VX
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                int nn = inst & 0x00FF;
                uint8_t rando = rand();
                uint8_t randod = rando & nn;
                memcpy(&state->V[x], &randod, sizeof(randod));
            } else if (CurrInst[0] == 'E' && CurrInst[2] == '9' && CurrInst[3] == 'E'){ // EX9E - Increment PC if key in VX is pressed
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;

                if (emstate->keypad[state->V[x]]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == 'E' && CurrInst[2] == 'A' && CurrInst[3] == '1'){ // EXA1 - Increment PC if key in VX is not pressed
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;

                if (!emstate->keypad[state->V[x]]) {
                    state->PC += 2;
                    jamp = true;
                    continue;
                }
            } else if (CurrInst[0] == 'F'){
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                char sub0 = CurrInst[2];
                char sub1 = CurrInst[3];

                if (sub0 == '0' && sub1 == '7'){ // FX07 - Set VX to value of Delay Timer
                    memcpy(&state->V[x], &state->DelayTimer, sizeof(state->DelayTimer));
                } else if (sub0 == '1' && sub1 == '5'){ // FX15 - Set Delay timer to value in VX
                    memcpy(&state->DelayTimer, &state->V[x], sizeof(state->V[x]));
                } else if (sub0 == '1' && sub1 == '8'){ // FX18 - Set Sound timer to value in VX
                    memcpy(&state->SoundTimer, &state->V[x], sizeof(state->V[x]));
                } else if (sub0 == '1' && sub1 == 'E'){ // FX1E - Add value of VX to I
                    state->I += state->V[x];
                } else if (sub0 == '0' && sub1 == 'A'){ // FX0A - Blocking Get Key, store key pressed in VX
                    dprint("Waiting for key\n");
                    while (!emstate->IsKeyPressed){
                        if (state->DelayTimer > 0) state->DelayTimer--;
                        if (state->SoundTimer > 0 && !IsSoundPlaying(tone)) {
                            PlaySound(tone);
                            state->SoundTimer--;
                        }
                        NSLP(16667);
                        WPollInputEvents(emstate);
                        printf("Polling for key... Current: %d\n", atomic_load(&emstate->IsKeyPressed));
                    }
                    memcpy(&state->V[x], &emstate->keypressed, sizeof(emstate->keypressed));
                    dprint("Got Key %x\n", state->V[x]);
                } else if (sub0 == '3' && sub1 == '3'){ // FX33 - Take number in VX, convert it to 3 Decimal Digits, and store it in RAM at Address in I
                    uint8_t val = state->V[x];
                    state->RAM[state->I + USR_RAM_OFFSET] = val / 100;
                    state->RAM[(state->I + USR_RAM_OFFSET) + 1] = (val / 10) % 10;
                    state->RAM[(state->I + USR_RAM_OFFSET) + 2] = val % 10;
                } else if (sub0 == '5' && sub1 == '5'){ // FX55 - Push All Registers to RAM at value of I
                    PushAllRegs(state, emstate);
                } else if (sub0 == '6' && sub1 == '5'){ // FX65 - Pop All Registers to RAM from value of I
                    PopAllRegs(state, emstate);
                }
            }
        }

        line = strtok(NULL, "\r\n");
        if (!jamp) state->PC++;
        if (state->DelayTimer > 0) state->DelayTimer--;
        if (state->SoundTimer > 0 && !IsSoundPlaying(tone)) {
            PlaySound(tone);
            state->SoundTimer--;
        }
        NSLP(16667);
    }
}