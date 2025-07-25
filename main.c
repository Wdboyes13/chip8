#include "state.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <omp.h>
#include "test.c"
#include "Input.h"

SDL_AudioDeviceID dev;
float tone[44100 / 60];

int main(){

    SDL_AudioSpec want = {
        .freq = 44100,
        .format = AUDIO_F32SYS,
        .channels = 1,
        .samples = 512,
        .callback = NULL, // Using queue audio instead
    };

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);
    if (dev == 0) {
        fprintf(stderr, "Failed to open audio: %s\n", SDL_GetError());
    }

    float freq = 440.0f; // A4 tone

    for (int i = 0; i < sizeof(tone) / sizeof(float); ++i) {
        tone[i] = 0.25f * sinf(2.0f * M_PI * freq * i / 44100.0f);
    }

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
            InputThread(emstate);
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