#pragma once

#include "common.h"

void FlipPixel(int x, int y, CHIP_State* state);
void FlipPRTC(int x, int y, CHIP_State* state, EmuState* emstate);
void PrintFontMember(FontArray letter, CHIP_State* state, EmuState* emstate);
void PrintChar(char c, EmuState* emstate, CHIP_State* state);
void ClearDisplay(CHIP_State* state);
void DrawSprite(uint8_t Vx, uint8_t Vy, uint8_t N, CHIP_State* state);