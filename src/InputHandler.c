//===------- InputHandler.c - Input Polling & Handling - C --------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#include "state.h"
#include <raylib.h>
#include <stdatomic.h>

void WPollInputEvents(EmuState* emstate) {

    for (int i = 0; i < 16; i++) {
        emstate->keypad[i] = false; // Reset all keys
    }

    if (IsKeyDown(KEY_ONE))       emstate->keypad[0x1] = true;
    if (IsKeyDown(KEY_TWO))       emstate->keypad[0x2] = true;
    if (IsKeyDown(KEY_THREE))     emstate->keypad[0x3] = true;
    if (IsKeyDown(KEY_FOUR))      emstate->keypad[0xC] = true;
    if (IsKeyDown(KEY_Q))         emstate->keypad[0x4] = true;
    if (IsKeyDown(KEY_W))         emstate->keypad[0x5] = true;
    if (IsKeyDown(KEY_E))         emstate->keypad[0x6] = true;
    if (IsKeyDown(KEY_R))         emstate->keypad[0xD] = true;
    if (IsKeyDown(KEY_A))         emstate->keypad[0x7] = true;
    if (IsKeyDown(KEY_S))         emstate->keypad[0x8] = true;
    if (IsKeyDown(KEY_D))         emstate->keypad[0x9] = true;
    if (IsKeyDown(KEY_F))         emstate->keypad[0xE] = true;
    if (IsKeyDown(KEY_Z))         emstate->keypad[0xA] = true;
    if (IsKeyDown(KEY_X))         emstate->keypad[0x0] = true;
    if (IsKeyDown(KEY_C))         emstate->keypad[0xB] = true;
    if (IsKeyDown(KEY_V))         emstate->keypad[0xF] = true;

    // Update key pressed flag & last key
    bool anyKeyPressed = false;
    for (int i = 0; i < 16; i++) {
        if (emstate->keypad[i]) {
            atomic_store(&emstate->IsKeyPressed, true);
            emstate->keypressed = i;
            anyKeyPressed = true;
            break;
        }
    }

    if (!anyKeyPressed) {
        atomic_store(&emstate->IsKeyPressed, false);
    }
}