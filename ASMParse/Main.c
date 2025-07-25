#include <stdio.h>
#include "LoadFile.h"
#include "Tokenize.h"
#include <stdlib.h>
#include <string.h>

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
            printf("\"00E0\\r\\n\",\n");
        } else if (strcmp("imov", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf("\"6%x%x\\r\\n\",\n", reg, numto);
        } else if (strcmp("ichar", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            printf("\"F%x29\\r\\n\",\n", reg);
        } else if (strcmp("drw", cargv[0]) == 0){
            // drw VX, VY, N - DXYN
            char *endx;
            int numx = hex_char_to_int(cargv[1][1]);
            int numy = hex_char_to_int(cargv[2][1]);;
            char *end;
            int numto = (int)strtol(cargv[3], &end, 0);

            printf("\"D%x%x%x\\r\\n\",\n", numx, numy, numto);
        } else if (strcmp("iadd", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf("\"7%x%x\\r\\n\",\n", reg, numto);
        } else if (strcmp("setidx", cargv[0]) == 0){
            int num = hex_char_to_int(cargv[1][1]);
            printf("\"A%x\\r\\n\",\n", num);
        } else if (strcmp("rand", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf("\"C%x%x\\r\\n\",\n", reg, numto);
        } else if (strcmp("jmp", cargv[0]) == 0){
            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf("\"1%x\\r\\n\",\n", num);
        } else if (strcmp("ret", cargv[0]) == 0){
            printf("\"00EE\\r\\n\",\n");
        } else if (strcmp("call", cargv[0]) == 0){
            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf("\"2%x\\r\\n\",\n", num);
        } else if (strcmp("ocall", cargv[0]) == 0){
            char *end;
            int num = (int)strtol(cargv[1], &end, 0);
            printf("\"B%x\\r\\n\",\n", num);
        } else if (strcmp("ipc.ie", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf("\"3%x%x\\r\\n\",\n", reg, numto);
        } else if (strcmp("ipc.ine", cargv[0]) == 0){
            char* regc = cargv[1];
            int reg = hex_char_to_int(regc[1]);
            char *end;
            int numto = (int)strtol(cargv[2], &end, 0);
            printf("\"4%x%x\\r\\n\",\n", reg, numto);
        } else if (strcmp("ipc.e", cargv[0]) == 0){
            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf("\"5%x%x0\\r\\n\",\n", regx, regy);
        } else if (strcmp("ipc.ne", cargv[0]) == 0){
            int regx = hex_char_to_int(cargv[1][1]);
            int regy = hex_char_to_int(cargv[2][1]);
            printf("\"9%x%x0\\r\\n\",\n", regx, regy);
        } else if (strcmp("pusha", cargv[0]) == 0){
            printf("\"FX55\\r\\n\",\n");
        } else if (strcmp("popa", cargv[0]) == 0){
            printf("\"FX65\\r\\n\",\n");
        }
    }
    printf("};\n");

}