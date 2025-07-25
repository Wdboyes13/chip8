//===------- Main.c - Main Assembler - C --------------------------------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#include <stdio.h>
#include "LoadFile.h"
#include "Tokenize.h"
#include <stdlib.h>
#include <string.h>

#define FMT_INST(INST) "\"" INST "\\r\\n\",\n"
#define APIN(...)  p += sprintf(p, __VA_ARGS__ );

int hex_char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; // Invalid hex character
}

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Usage: %s <filename> <output>\n", argv[0]);
        return 1;
    }

    FILE* ofile = fopen(argv[2], "wb");
    if (!ofile) {
        perror("fopen");
        return 1;
    }

    FILE* f = LdFile(argv[1]);
    if (!f) {
        perror("fopen");
        return 1;
    }

    int lines = CLines(argv[1]);
    lines++;

    char* ostring = malloc(lines * 20);
    char* p = ostring;

    printf("char exec[] = {\n");
    for (int i = 0; i < lines; i++){
        const char* str = RdLine(f);
        char* cargv[MAX_TOKENS] = {0};
        Tokenize(str, cargv);
        if (strcmp("cls", cargv[0]) == 0){

            printf(FMT_INST("00E0"));
            APIN("00E0\r\n");

        } else if (strcmp("imov", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("6%x%02x"), reg, numto);
            APIN("6%1x%02x\r\n", reg, numto);

        } else if (strcmp("ichar", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x29"), reg);
            APIN("F%1x29\r\n", reg);

        } else if (strcmp("drw", cargv[0]) == 0){

            // drw VX, VY, N - DXYN
            char *endx;
            int numx = hex_char_to_int(cargv[1][1]);
            int numy = hex_char_to_int(cargv[2][1]);;
            char *end;
            int numto = (int)strtol(cargv[3], &end, 0);

            printf(FMT_INST("D%1x%1x%1x"), numx, numy, numto);
            APIN("D%1x%1x%1x\r\n", numx, numy, numto);

        } else if (strcmp("iadd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("7%1x%02x"), reg, numto);
            APIN("7%1x%02x\r\n", reg, numto)

        } else if (strcmp("setidx", cargv[0]) == 0){

            int num = hex_char_to_int(cargv[1][1]);
            printf(FMT_INST("A%3x"), num);
            APIN("A%3x\r\n", num);

        } else if (strcmp("rand", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("C%1x%02x"), reg, numto);
            APIN("C%1x%02x\r\n", reg, numto)

        } else if (strcmp("jmp", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("1%3x"), num);
            APIN("1%3x\r\n", num);

        } else if (strcmp("ret", cargv[0]) == 0){

            printf(FMT_INST("00EE"));
            APIN("00EE\r\n");

        } else if (strcmp("call", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("2%3x"), num);
            APIN("2%3x\r\n", num);

        } else if (strcmp("ocall", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("B%3x"), num);
            APIN("B%3x\r\n", num);

        } else if (strcmp("ipc.ie", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("3%1x%02x"), reg, numto);
            APIN("3%1x%02x\r\n", reg, numto);

        } else if (strcmp("ipc.ine", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("4%1x%02x"), reg, numto);
            APIN("4%1x%02x\r\n", reg, numto);

        } else if (strcmp("ipc.e", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("5%1x%1x0"), regx, regy);
            APIN("5%1x%1x0\r\n", regx, regy);

        } else if (strcmp("ipc.ne", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("9%1x%1x0"), regx, regy);
            APIN("9%1x%1x0\r\n", regx, regy);

        } else if (strcmp("pusha", cargv[0]) == 0){

            printf(FMT_INST("FX55"));
            APIN("FX55\r\n");

        } else if (strcmp("popa", cargv[0]) == 0){

            printf(FMT_INST("FX65"));
            APIN("FX65\r\n");

        } else if (strcmp("tm.gd", cargv[0]) == 0){
            
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x07"), reg);
            APIN("F%1x07\r\n", reg);

        } else if (strcmp("tm.sd", cargv[0]) == 0){
            
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x15"), reg);
            APIN("F%1x15\r\n", reg);

        } else if (strcmp("tm.ss", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x18"), reg);
            APIN("F%1x18\r\n", reg);

        } else if (strcmp("idxadd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x1E"), reg);
            APIN("F%1x1E\r\n", reg);

        } else if (strcmp("gkey", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x0A"), reg);
            APIN("F%1x0A\r\n", reg);

        } else if (strcmp("bcd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%1x33"), reg);
            APIN("F%1x33\r\n", reg);

        } else if (strcmp("del", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("D%1xF0"), reg);
            APIN("D%1xF0\r\n", reg);

        } else if (strcmp("in.p", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("E%1x9A"), reg);
            APIN("E%1x9A\r\n", reg);

        } else if (strcmp("in.np", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("E%1xA1"), reg);
            APIN("E%1xA1\r\n", reg);

        } else if (strcmp("mov", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x0"), regx, regy);
            APIN("8%1x%1x0\r\n", regx, regy);

        } else if (strcmp("r.or", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x1"), regx, regy);
            APIN("8%1x%1x1\r\n", regx, regy);
            
        } else if (strcmp("r.and", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x2"), regx, regy);
            APIN("8%1x%1x2\r\n", regx, regy);
            
        } else if (strcmp("r.xor", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x3"), regx, regy);
            APIN("8%1x%1x3\r\n", regx, regy);
            
        } else if (strcmp("r.add", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x4"), regx, regy);
            APIN("8%1x%1x4\r\n", regx, regy);
            
        } else if (strcmp("r.lsub", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x5"), regx, regy);
            APIN("8%1x%1x5\r\n", regx, regy);
            
        } else if (strcmp("r.rsub", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x7"), regx, regy);
            APIN("8%1x%1x7\r\n", regx, regy);
            
        } else if (strcmp("r.bsr", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1x6"), regx, regy);
            APIN("8%1x%1x6\r\n", regx, regy);
            
        } else if (strcmp("r.bsl", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%1x%1xE"), regx, regy);
            APIN("8%1x%1xE\r\n", regx, regy);
            
        }
    }
    printf("};\n");
    fwrite(ostring, strlen(ostring), 1, ofile);
    fclose(ofile);
    return 0;
}