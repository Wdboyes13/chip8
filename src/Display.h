//===------- Display.h - Header for Display Functions - C Header --------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#pragma once

#include "common.h"

void FlipPixel(int x, int y, CHIP_State* state);
void FlipPRTC(int x, int y, CHIP_State* state, EmuState* emstate);
void PrintFontMember(FontArray letter, CHIP_State* state, EmuState* emstate);
void PrintChar(char c, EmuState* emstate, CHIP_State* state);
void ClearDisplay(CHIP_State* state);
void DrawSprite(uint8_t Vx, uint8_t Vy, uint8_t N, CHIP_State* state);