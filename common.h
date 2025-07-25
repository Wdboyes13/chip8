#pragma once

#include <stdbool.h>
#include "state.h"

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