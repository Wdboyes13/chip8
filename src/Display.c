//===------- Display.c - Functions for display - C -----------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#include "state.h"
#include "raylib.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>

void FlipPixel(int x, int y, CHIP_State* state){
    state->Display[x][y] = !state->Display[x][y];
    printf("Printing pixel at %d,%d\n", x, y);
}

void ClearDisplay(CHIP_State* state){
    for (int x = 0; x < EMU_WIDTH; x++) {
        for (int y = 0; y < EMU_HEIGHT; y++){
            state->Display[x][y] = false;
        }
    }
}

void DrawSprite(uint8_t Vx, uint8_t Vy, uint8_t N, CHIP_State* state) {
    state->V[0xF] = 0;  // Reset collision flag

    for (int row = 0; row < N; row++) {
        uint8_t spriteByte = state->RAM[state->I + row];

        for (int col = 0; col < 8; col++) {
            // Get the current bit (MSB to LSB)
            uint8_t spritePixel = (spriteByte >> (7 - col)) & 1;
            if (spritePixel == 0) continue;

            int x = (Vx + col) % EMU_WIDTH;
            int y = (Vy + row) % EMU_HEIGHT;

            if (state->Display[x][y]) {
                state->V[0xF] = 1;  // Set collision flag
            }

            state->Display[x][y] ^= 1;  // XOR the pixel
        }
    }
}

void InitDisplay(EmuState* emstate){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CHIP-8");
    SetTargetFPS(60);
    emstate->InitializedDisplay = true;
}

void FlipPRTC(int x, int y, CHIP_State* state, EmuState* emstate){
    int dx = emstate->CursorX + x;
    int dy = emstate->CursorY + y;
    FlipPixel(dx, dy, state);
    printf("Printing %d,%d\n", dx, dy);
}

void PrintFontMember(FontArray letter, CHIP_State* state, EmuState* emstate){
    for (int row = 0; row < FONTH; row++) {           // top to bottom
        printf("IN ROW LOOP\n");
        for (int col = 0; col < FONTW; col++) {
            printf("IN COL LOOP\n");
            if (letter[row][col]) {
                printf("CURRENT IS TRUE %d,%d", row, col);
                FlipPRTC(col, row, state, emstate);   // draw normally
            }
        }
    }

    // Move to next char
    emstate->CursorX += FONTW + 1;
    if (emstate->CursorX >= EMU_WIDTH) {
        emstate->CursorX = 0;
        emstate->CursorY += FONTH;
    }
}

void PrintChar(char c, EmuState* emstate, CHIP_State* state){
    switch (c){
        case 'A': PrintFontMember(ASCII.LA, state, emstate); break;
        case 'B': PrintFontMember(ASCII.LB, state, emstate); break;
        case 'C': PrintFontMember(ASCII.LC, state, emstate); break;
        case 'D': PrintFontMember(ASCII.LD, state, emstate); break;
        case 'E': PrintFontMember(ASCII.LE, state, emstate); break;
        case 'F': PrintFontMember(ASCII.LF, state, emstate); break;
        case 'G': PrintFontMember(ASCII.LG, state, emstate); break;
        case 'H': PrintFontMember(ASCII.LH, state, emstate); break;
        case 'I': PrintFontMember(ASCII.LI, state, emstate); break;
        case 'J': PrintFontMember(ASCII.LJ, state, emstate); break;
        case 'K': PrintFontMember(ASCII.LK, state, emstate); break;
        case 'L': PrintFontMember(ASCII.LL, state, emstate); break;
        case 'M': PrintFontMember(ASCII.LM, state, emstate); break;
        case 'N': PrintFontMember(ASCII.LN, state, emstate); break;
        case 'O': PrintFontMember(ASCII.LO, state, emstate); break;
        case 'P': PrintFontMember(ASCII.LP, state, emstate); break;
        case 'Q': PrintFontMember(ASCII.LQ, state, emstate); break;
        case 'R': PrintFontMember(ASCII.LR, state, emstate); break;
        case 'S': PrintFontMember(ASCII.LS, state, emstate); break;
        case 'T': PrintFontMember(ASCII.LT, state, emstate); break;
        case 'U': PrintFontMember(ASCII.LU, state, emstate); break;
        case 'V': PrintFontMember(ASCII.LV, state, emstate); break;
        case 'W': PrintFontMember(ASCII.LW, state, emstate); break;
        case 'X': PrintFontMember(ASCII.LX, state, emstate); break;
        case 'Y': PrintFontMember(ASCII.LY, state, emstate); break;
        case 'Z': PrintFontMember(ASCII.LZ, state, emstate); break;
        case '0': PrintFontMember(ASCII.L0, state, emstate); break;
        case '1': PrintFontMember(ASCII.L1, state, emstate); break;
        case '2': PrintFontMember(ASCII.L2, state, emstate); break;
        case '3': PrintFontMember(ASCII.L3, state, emstate); break;
        case '4': PrintFontMember(ASCII.L4, state, emstate); break;
        case '5': PrintFontMember(ASCII.L5, state, emstate); break;
        case '6': PrintFontMember(ASCII.L6, state, emstate); break;
        case '7': PrintFontMember(ASCII.L7, state, emstate); break;
        case '8': PrintFontMember(ASCII.L8, state, emstate); break;
        case '9': PrintFontMember(ASCII.L9, state, emstate); break;
        case ' ': PrintFontMember(ASCII.SPACE, state, emstate); break;
        default:
            // Optional: Print something like a question mark or a blank space
            PrintFontMember(ASCII.UNKNOWN, state, emstate);
            break;
    }
}

void DoDisplay(EmuState* emstate, CHIP_State* state){
    if (emstate->InitializedDisplay){
        while (!WindowShouldClose()){
            BeginDrawing();
            ClearBackground(BLACK);
            for (int y = 0; y < EMU_HEIGHT; y++){
                for (int x = 0; x < EMU_WIDTH; x++){
                    if (state->Display[x][y]){
                        DrawRectangle(x * PIX_SCALE, y * PIX_SCALE, PIX_SCALE, PIX_SCALE, WHITE);
                    }
                }
            }
            EndDrawing();
        }
        CloseWindow();
    } else {
        InitDisplay(emstate);
        DoDisplay(emstate, state);
    }
}

void SetIToChar(CHIP_State* state){
    
}