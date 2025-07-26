#include "state.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <omp.h>
#include "test.c"

SDL_AudioDeviceID dev;
float tone[44100 / 60];

char* LdExec(const char* fname);

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }
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
    printf("Set States\n");

    emstate->CursorX = 0;
    emstate->CursorY = 0;

    srand(time(NULL));
    InitFontSet(state);
    for(int y = 0; y < EMU_HEIGHT; y++){
        for(int x = 0; x < EMU_WIDTH; x++){
            state->Display[x][y] = false;
        }
    }

    printf("Enterring Parallel\n");

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            DoDisplay(emstate, state);
        }
        #pragma omp section
        {
            printf("Starting CPU\n");
            RunCPU(state, emstate, LdExec(argv[1]));
        }
    }

    if (state) free(state);
    if (emstate) free(emstate);

    return 0;
}