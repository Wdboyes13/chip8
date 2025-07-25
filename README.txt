A simple CHIP-8 emulator

using guide https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

you'll need libomp (OpenMP) and liSDL2 (SDL2) and libraylib (Raylib)
it will not work on windows unless you somehow get unistd.h to work 

supported instructions are in Supported.txt 
the loaded binary is in test.c and instructions are CRLF ("\r\n") separated