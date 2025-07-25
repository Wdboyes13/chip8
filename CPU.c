#include "common.h"
#include <unistd.h>
#include "Display.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void RunCPU(CHIP_State* state, EmuState* emstate, char exec[]){
    int execlen = 1;
    state->PC = 0;
    while (!emstate->InitializedDisplay) {
        usleep(200000);
    }
    char* line = strtok(exec, "\r\n");
    while (line != NULL) {
        char CurrInst[5];

        if (sscanf(line, "%4s", CurrInst) == 1) {
            // Now CurrInst contains the opcode as a 16-bit integer
            printf("Fetched instruction: 0x%s\n", CurrInst);
            if (strcmp(CurrInst, "00E0") == 0){
                ClearDisplay(state);
            } else if (CurrInst[0] == '1'){
                const char* sub = CurrInst + 1;
                state->PC = (uint16_t)strtol(sub, NULL, 16);
            } else if (CurrInst[0] == '6'){
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                int regnum = (inst & 0x0F00) >> 8;
                int regval = inst & 0x00FF;
                state->V[regnum] = regval;
            } else if (CurrInst[0] == '7'){
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                int regnum = (inst & 0x0F00) >> 8;
                int regval = inst & 0x00FF;
                state->V[regnum] += regval;
            } else if (CurrInst[0] == 'A'){
                const char* sub = CurrInst + 1;
                state->I = (uint16_t)strtol(sub, NULL, 16);
            } else if (CurrInst[0] == 'D'){
                uint16_t inst = (uint16_t)strtol(CurrInst, NULL, 16);
                uint8_t x = (inst & 0x0F00) >> 8;
                uint8_t y = (inst & 0x00F0) >> 4;
                uint8_t height = inst & 0x000F;
                DrawSprite(state->V[x], state->V[y], height, state);
            } else if (CurrInst[0] == 'F' && CurrInst[2] == '2' && CurrInst[3] == '9'){
                int x;
                sscanf(&CurrInst[1], "%1X", &x);
                uint16_t fontdex = state->V[x];
                state->I = 0x300 + fontdex * 5;
                printf("FX29 on V[%d] = %d, I = 0x%X\n", x, fontdex, state->I);
            }
        }

        line = strtok(NULL, "\r\n");
        state->PC++; // You may increment PC differently based on CHIP-8 logic
        usleep(200000);
    }
}