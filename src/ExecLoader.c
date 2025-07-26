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
    return exec;
}