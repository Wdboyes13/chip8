//===------- LoadFile.c - Assembly file loader, and read functions - C --------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* LdFile(const char* name){
    FILE* file = fopen(name, "r");
    if (!file) {
        perror("fopen");
        exit(1);
    }
    return file;
}

const char* RdLine(FILE* file) {
    char buffer[1024];  // Static buffer; change size as needed
    if (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline if any

        const char* line = buffer;
        return strdup(line);
    } else {
        printf("Failed to read a line\n");
        return NULL;
    }
}


int CLines(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return -1;
    }

    int lines = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}