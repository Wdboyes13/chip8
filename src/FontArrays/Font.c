//===------- Font.c - A simple ASCII font - C ----------------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../common.h"
#define Y true 
#define N false 

static FontArray A = {
    {N, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
};

static FontArray B = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray C = {
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, Y, Y, Y}
};

static FontArray D = {
    {Y, Y, Y, N},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, N}
};

static FontArray E = {
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, Y, Y, N},
    {Y, N, N, N},
    {Y, Y, Y, Y}
};

static FontArray F = {
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, Y, Y, N},
    {Y, N, N, N},
    {Y, N, N, N}
};

static FontArray G = {
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray H = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, N, N, Y}
};

static FontArray I = {
    {Y, Y, Y, Y},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {Y, Y, Y, Y}
};

static FontArray J = {
    {Y, Y, Y, Y},
    {N, N, Y, N},
    {N, N, Y, N},
    {Y, N, Y, N},
    {N, Y, N, N}
};

static FontArray K = {
    {Y, N, N, Y},
    {Y, N, Y, N},
    {Y, Y, N, N},
    {Y, N, Y, N},
    {Y, N, N, Y}
};

static FontArray L = {
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, Y, Y, Y}
};

static FontArray M = {
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y}
};

static FontArray NN = {
    {Y, N, N, Y},
    {Y, Y, N, Y},
    {Y, N, Y, Y},
    {Y, N, Y, Y},
    {Y, N, N, Y}
};

static FontArray O = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray P = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, N, N, N}
};

static FontArray Q = {
    {Y, Y, Y, N},
    {Y, N, Y, N},
    {Y, Y, Y, N},
    {N, N, Y, N},
    {N, N, N, Y}
};

static FontArray R = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, Y, N},
    {Y, N, N, Y}
};

static FontArray S = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {N, Y, N, N},
    {Y, N, Y, N},
    {Y, Y, Y, Y}
};

static FontArray T = {
    {Y, Y, Y, Y},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {N, Y, Y, N}
};

static FontArray U = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray V = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {N, Y, Y, N},
    {N, Y, Y, N}
};

static FontArray W = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y}
};

static FontArray X = {
    {Y, N, N, Y},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {Y, N, N, Y}
};

static FontArray YY = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {N, Y, Y, N},
    {N, Y, Y, N},
    {N, Y, Y, N}
};

static FontArray Z = {
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {N, N, Y, N},
    {N, Y, N, N},
    {Y, Y, Y, Y}
};

static FontArray L1 = {
    {Y, Y, N, N},
    {N, Y, N, N},
    {N, Y, N, N},
    {N, Y, N, N},
    {Y, Y, Y, N}
};

static FontArray L2 = {
    {Y, Y, Y, N},
    {N, N, Y, N},
    {N, Y, N, N},
    {Y, N, N, N},
    {Y, Y, Y, Y}
};

static FontArray L3 = {
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray L4 = {
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {N, N, N, Y}
};

static FontArray L5 = {
    {Y, Y, Y, Y},
    {Y, N, N, N},
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray L6 = {
    {Y, N, N, N},
    {Y, N, N, N},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray L7 = {
    {Y, Y, Y, Y},
    {N, N, Y, N},
    {N, Y, N, N},
    {Y, N, N, N}
};

static FontArray L8 = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

static FontArray L9 = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y},
    {N, N, N, Y},
    {N, N, N, Y}
};

static FontArray L0 = {
    {Y, Y, Y, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, N, N, Y},
    {Y, Y, Y, Y}
};

FontSet ASCII = {0};

#define CPYLET(Letter) memcpy(ASCII.L##Letter , Letter, sizeof(FontArray))


void ConvertFontToSprite(FontArray letter, uint8_t* outBytes) {
    for (int row = 0; row < FONTH; row++) {
        uint8_t byte = 0;
        for (int col = 0; col < FONTW; col++) {
            if (letter[row][col]) {
                byte |= (1 << (7 - col));  // Left-align to high bits
            }
        }
        outBytes[row] = byte;
    }
}

#define CPYCHAR(Letter, X) ConvertFontToSprite(Letter , &state->RAM[(base) + (X) * 5]);

void InitFontSet(CHIP_State* state) {
    int base = 0x300;
    CPYCHAR(A, 0);
    CPYCHAR(B, 1);
    CPYCHAR(C, 2);
    CPYCHAR(D, 3);
    CPYCHAR(E, 4);
    CPYCHAR(F, 5);
    CPYCHAR(G, 6);
    CPYCHAR(H, 7);
    CPYCHAR(I, 8);
    CPYCHAR(J, 9);
    CPYCHAR(K, 10);
    CPYCHAR(L, 11);
    CPYCHAR(M, 12);
    CPYCHAR(NN, 13);
    CPYCHAR(O, 14);
    CPYCHAR(P, 15);
    CPYCHAR(Q, 16);
    CPYCHAR(R, 17);
    CPYCHAR(S, 18);
    CPYCHAR(T, 19);
    CPYCHAR(U, 20);
    CPYCHAR(V, 21);
    CPYCHAR(W, 22);
    CPYCHAR(X, 23);
    CPYCHAR(YY, 24);
    CPYCHAR(Z, 25);

    CPYCHAR(L0, 26);
    CPYCHAR(L1, 27);
    CPYCHAR(L2, 28);
    CPYCHAR(L3, 29);
    CPYCHAR(L4, 30);
    CPYCHAR(L5, 31);
    CPYCHAR(L6, 32);
    CPYCHAR(L7, 33);
    CPYCHAR(L8, 34);
    CPYCHAR(L9, 35);
}