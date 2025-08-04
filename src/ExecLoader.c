//===------- ExecLoader.c - Executable Loader & Parser - C ---------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state.h"

#define EXE_MAX 2048

char* LdExec(const char* fname) {
    char* exec = malloc(EXE_MAX);
    if (!exec) {
        perror("malloc");
        return NULL;
    }

    FILE* file = fopen(fname, "rb");
    if (!file) {
        perror("fopen");
        free(exec);
        return NULL;
    }

    size_t len = fread(exec, 1, EXE_MAX - 1, file);
    exec[len] = '\0';  // Null-terminate the buffer for strtok
    fclose(file);

    printf("Loaded executable: %s\n", exec);

    uint8_t* ExecutableLoadedMemory = calloc(4096, sizeof(uint8_t));  // full memory map

    char* line = strtok(exec, "\r\n");
    uint16_t load_address = EXEC_OFFSET;

    while (line != NULL) {
        uint16_t inst;
        sscanf(line, "%4hx", &inst); // read 2-byte instruction from hex
        ExecutableLoadedMemory[load_address++] = (inst >> 8) & 0xFF;
        ExecutableLoadedMemory[load_address++] = inst & 0xFF;
        line = strtok(NULL, "\r\n");
    }
    
    return exec;
}