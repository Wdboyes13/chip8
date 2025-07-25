#include "state.h"
#include <SDL2/SDL.h>

void InputThread(EmuState* emstate) {
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                bool pressed = (event.type == SDL_KEYDOWN);
                switch (event.key.keysym.sym) {
                    case SDLK_1: emstate->keypad[0x1] = pressed; break;
                    case SDLK_2: emstate->keypad[0x2] = pressed; break;
                    case SDLK_3: emstate->keypad[0x3] = pressed; break;
                    case SDLK_4: emstate->keypad[0xC] = pressed; break;
                    case SDLK_q: emstate->keypad[0x4] = pressed; break;
                    case SDLK_w: emstate->keypad[0x5] = pressed; break;
                    case SDLK_e: emstate->keypad[0x6] = pressed; break;
                    case SDLK_r: emstate->keypad[0xD] = pressed; break;
                    case SDLK_a: emstate->keypad[0x7] = pressed; break;
                    case SDLK_s: emstate->keypad[0x8] = pressed; break;
                    case SDLK_d: emstate->keypad[0x9] = pressed; break;
                    case SDLK_f: emstate->keypad[0xE] = pressed; break;
                    case SDLK_z: emstate->keypad[0xA] = pressed; break;
                    case SDLK_x: emstate->keypad[0x0] = pressed; break;
                    case SDLK_c: emstate->keypad[0xB] = pressed; break;
                    case SDLK_v: emstate->keypad[0xF] = pressed; break;
                }
            }
        }
        if (emstate->keypad[0x0]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x0;
        }
        if (emstate->keypad[0x1]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x1;
        }
        if (emstate->keypad[0x2]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x2;
        }
        if (emstate->keypad[0x3]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x3;
        }
        if (emstate->keypad[0x4]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x4;
        }
        if (emstate->keypad[0x5]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x5;
        }
        if (emstate->keypad[0x6]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x6;
        }
        if (emstate->keypad[0x7]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x7;
        }
        if (emstate->keypad[0x8]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x8;
        }
        if (emstate->keypad[0x9]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0x9;
        }
        if (emstate->keypad[0xA]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xA;
        }
        if (emstate->keypad[0xB]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xB;
        }
        if (emstate->keypad[0xC]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xC;
        }
        if (emstate->keypad[0xD]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xD;
        }
        if (emstate->keypad[0xE]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xE;
        }
        if (emstate->keypad[0xF]) {
            emstate->IsKeyPressed = true; emstate->keypressed = 0xF;
        }
        SDL_Delay(1); // Avoid burning CPU
    }
}

