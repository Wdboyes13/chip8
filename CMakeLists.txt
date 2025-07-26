cmake_minimum_required(VERSION 3.10)

project (
    chip8
    LANGUAGES C 
    HOMEPAGE_URL https://github.com/Wdboyes13/chip8
    VERSION 1.2.0
)

set(CMAKE_C_STANDARD 99)
find_package(SDL2 REQUIRED)

add_executable( chip8
    src/CPU.c src/Display.c
    src/InputHandler.c src/main.c
    src/Poppers.c src/FontArrays/Font.c
    src/ExecLoader.c
)

target_compile_options( chip8 PRIVATE -fopenmp -O2 )

if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    message(STATUS "Clang detected, linking OpenMP manually")
    target_link_options( chip8 PRIVATE -lomp )
endif()

target_link_libraries( chip8 PRIVATE raylib )

if(APPLE)
    target_link_libraries(chip8
        PRIVATE
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
            "-framework CoreFoundation"
            "-framework AppKit"
            "-framework QuartzCore"
    )
endif()

add_executable( chip8-as
    src/ASMParse/LoadFile.c src/ASMParse/Main.c
    src/ASMParse/Tokenize.c
)

