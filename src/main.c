#include "state.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include <omp.h>
#include "test.c"
#include <time.h>

char* LdExec(const char* fname);

#define SAMPLE_RATE 44100
#define TONE_DURATION_SECONDS 1.0f
#define FREQUENCY 440.0f

Sound tone;

void GenerateTone(float freq) {
    int sampleCount = (int)(SAMPLE_RATE * TONE_DURATION_SECONDS);
    float *samples = (float *)malloc(sampleCount * sizeof(float));

    for (int i = 0; i < sampleCount; i++) {
        samples[i] = 0.25f * sinf(2.0f * PI * freq * i / SAMPLE_RATE);
    }

    Wave wave = {
        .frameCount = sampleCount,
        .sampleRate = SAMPLE_RATE,
        .sampleSize = 32,
        .channels = 1,
        .data = samples
    };

    tone = LoadSoundFromWave(wave);

    // Clean up wave (copies sample data into tone)
    UnloadWave(wave);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    InitAudioDevice();
    GenerateTone(FREQUENCY);

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
    UnloadSound(tone);
    CloseAudioDevice();

    return 0;
}