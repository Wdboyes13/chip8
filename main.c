#include "state.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <omp.h>
#include "test.c"

int main(){
    EmuState* emstate = malloc(sizeof(EmuState));
    if (emstate == NULL) {
        printf("Error: Failed to allocate Emulator state\n");
        return 1;
    }

    CHIP_State* state = malloc(sizeof(CHIP_State));
    if (state == NULL) {
        printf("Error: Failed to allocate state\n");
        return 1;
    }
    emstate->AllocatedState = true;
    emstate->CursorX = 0;
    emstate->CursorY = 0;
    srand(time(NULL));
    InitFontSet(state);
    for(int y = 0; y < EMU_HEIGHT; y++){
        for(int x = 0; x < EMU_WIDTH; x++){
            state->Display[x][y] = false;
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            DoDisplay(emstate, state);
        }
        #pragma omp section
        {
            RunCPU(state, emstate, exec);
        }
    }

    if (state) free(state);
    if (emstate) free(emstate);

    return 0;
}