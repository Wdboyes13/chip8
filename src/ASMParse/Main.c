#include <stdio.h>
#include "LoadFile.h"
#include "Tokenize.h"
#include <stdlib.h>
#include <string.h>

#define FMT_INST(INST) "\"" INST "\\r\\n\",\n"

int hex_char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; // Invalid hex character
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE* f = LdFile(argv[1]);
    int lines = CLines(argv[1]);
    lines++;
    printf("char exec[] = {\n");
    for (int i = 0; i < lines; i++){
        const char* str = RdLine(f);
        char* cargv[MAX_TOKENS] = {0};
        Tokenize(str, cargv);
        if (strcmp("cls", cargv[0]) == 0){

            printf(FMT_INST("00E0"));

        } else if (strcmp("imov", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("6%x%x"), reg, numto);

        } else if (strcmp("ichar", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x29"), reg);

        } else if (strcmp("drw", cargv[0]) == 0){

            // drw VX, VY, N - DXYN
            char *endx;
            int numx = hex_char_to_int(cargv[1][1]);
            int numy = hex_char_to_int(cargv[2][1]);;
            char *end;
            int numto = (int)strtol(cargv[3], &end, 0);

            printf(FMT_INST("D%x%x%x"), numx, numy, numto);

        } else if (strcmp("iadd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("7%x%x"), reg, numto);

        } else if (strcmp("setidx", cargv[0]) == 0){

            int num = hex_char_to_int(cargv[1][1]);
            printf(FMT_INST("A%x"), num);

        } else if (strcmp("rand", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("C%x%x"), reg, numto);

        } else if (strcmp("jmp", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("1%x"), num);

        } else if (strcmp("ret", cargv[0]) == 0){

            printf(FMT_INST("00EE"));

        } else if (strcmp("call", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("2%x"), num);

        } else if (strcmp("ocall", cargv[0]) == 0){

            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf(FMT_INST("B%x"), num);

        } else if (strcmp("ipc.ie", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("3%x%x"), reg, numto);

        } else if (strcmp("ipc.ine", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf(FMT_INST("4%x%x"), reg, numto);

        } else if (strcmp("ipc.e", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("5%x%x0"), regx, regy);

        } else if (strcmp("ipc.ne", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("9%x%x0"), regx, regy);

        } else if (strcmp("pusha", cargv[0]) == 0){

            printf(FMT_INST("FX55"));

        } else if (strcmp("popa", cargv[0]) == 0){

            printf(FMT_INST("FX65"));

        } else if (strcmp("tm.gd", cargv[0]) == 0){
            
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x07"), reg);

        } else if (strcmp("tm.sd", cargv[0]) == 0){
            
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x15"), reg);

        } else if (strcmp("tm.ss", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x18"), reg);

        } else if (strcmp("idxadd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x1E"), reg);

        } else if (strcmp("gkey", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x0A"), reg);

        } else if (strcmp("bcd", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("F%x33"), reg);

        } else if (strcmp("del", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("D%xF0"), reg);

        } else if (strcmp("in.p", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("E%x9A"), reg);

        } else if (strcmp("in.np", cargv[0]) == 0){

            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf(FMT_INST("E%xA1"), reg);

        } else if (strcmp("mov", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x0"), regx, regy);

        } else if (strcmp("r.or", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x1"), regx, regy);
            
        } else if (strcmp("r.and", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x2"), regx, regy);
            
        } else if (strcmp("r.xor", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x3"), regx, regy);
            
        } else if (strcmp("r.add", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x4"), regx, regy);
            
        } else if (strcmp("r.lsub", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x5"), regx, regy);
            
        } else if (strcmp("r.rsub", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x7"), regx, regy);
            
        } else if (strcmp("r.bsr", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%x6"), regx, regy);
            
        } else if (strcmp("r.bsl", cargv[0]) == 0){

            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf(FMT_INST("8%x%xE"), regx, regy);
            
        }
    }
    printf("};\n");

}