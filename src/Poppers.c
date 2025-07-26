#include "common.h"
#include <string.h> // Because some idiot thought putting `memcpy` in string.h was smart
#define IStart() uint16_t IStart = (state->I + USR_RAM_OFFSET)

#define PushReg(IDX) memcpy(&state->RAM[ IStart + IDX ], &state->V[ IDX ], sizeof(state->V[ IDX ]))
#define PopReg(IDX) memcpy(&state->V[ IDX ], &state->RAM[ IStart + IDX ], sizeof(state->V[ IDX ]))

void PopAllRegs(CHIP_State* state, EmuState* emstate){
    IStart();
    PopReg(0);
    PopReg(1);
    PopReg(2);
    PopReg(3);
    PopReg(4);
    PopReg(5);
    PopReg(6);
    PopReg(7);
    PopReg(8);
    PopReg(9);
    PopReg(10);
    PopReg(11);
    PopReg(12);
    PopReg(13);
    PopReg(14);
    PopReg(15);
}

void PushAllRegs(CHIP_State* state, EmuState* emstate){
    IStart();
    PushReg(0);
    PushReg(1);
    PushReg(2);
    PushReg(3);
    PushReg(4);
    PushReg(5);
    PushReg(6);
    PushReg(7);
    PushReg(8);
    PushReg(9);
    PushReg(10);
    PushReg(11);
    PushReg(12);
    PushReg(13);
    PushReg(14);
    PushReg(15);
}