//===------- Tokenize.c - Function to Tokenize a Loaded Assembly File ---------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#include <stdlib.h>
#include <string.h>
#include "Tokenize.h"

int Tokenize(const char *line, char *argv[]) {
    int argc = 0;
    char *copy = strdup(line); // Make a mutable copy
    char *token = strtok(copy, " ,\t\n");

    while (token && argc < MAX_TOKENS) {
        argv[argc++] = token;
        token = strtok(NULL, " ,\t\n");
    }

    argv[argc] = NULL; // Null-terminate like real argv
    return argc;
}