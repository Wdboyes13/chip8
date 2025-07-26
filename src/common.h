//===------- common.h - Common Header providing many things - C Header -*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#pragma once

#include <stdbool.h>
#include "state.h"
#include <raylib.h>

#define PIX_SCALE 10

#define SCREEN_WIDTH (PIX_SCALE * 64)
#define SCREEN_HEIGHT (PIX_SCALE * 32)

#define EMU_WIDTH 64
#define EMU_HEIGHT 32

#define FONTH 5
#define FONTW 4

typedef bool FontArray[5][4];

typedef struct FontSet {
    FontArray LA, LB, LC, LD, LE, 
              LF, LG, LH, LI, LJ, 
              LK, LL, LM, LN, LO, 
              LP, LQ, LR, LS, LT, 
              LU, LV, LW, LX, LY, 
              LZ;

    FontArray L0, L1, L2, L3, L4,
              L5, L6, L7, L8, L9;
              
    FontArray UNKNOWN, SPACE;
} FontSet;

extern FontSet ASCII;

void DoDisplay(EmuState* emstate, CHIP_State* state);
void RunCPU(CHIP_State* state, EmuState* emstate, char exec[]);
void InitFontSet(CHIP_State* state);

#ifdef DBG
  #define dprint(...) printf(__VA_ARGS__)
#else
  #define dprint(...) ((void)0)
#endif

extern Sound tone;

void PopAllRegs(CHIP_State* state, EmuState* emstate);
void PushAllRegs(CHIP_State* state, EmuState* emstate);

void WPollInputEvents(EmuState* emstate);

#ifdef _WIN32 
#include <windows.h>
#define NSLP(microsecs) Sleep( microsecs / 1000 )
#define SSLP(secs) Sleep( secs * 1000 )
#else 
#include <unistd.h>
#define NSLP(microsecs) usleep(microsecs)
#define SSLP(secs) sleep(secs)
#endif