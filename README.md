# A simple CHIP-8 emulator
# I used this guide! https://tobiasvl.github.io/blog/write-a-chip-8-emulator/

## Requirements
- Raylib (Included in [vendor/raylib](/vendor/raylib/))  
- OpenMP (Included with most compilers)  
- CMake  

## How to build
To build, just run `cmake -S . -B build -G Ninja`  
Then run `ninja -C build`  

## Where are the docs?
Supported instructions are in [docs/ISA.md](/docs/ISA.md)  
To make your own binary, use `chip8-as` the assembler  
Use it like `chip8-as input.s output.bin` and to run it, `chip8 output.bin`  

## How to build required libraries  
To build raylib, make sure your Working Directory is vendor/raylib  
Then do `cmake -B build -S . -G Ninja` to setup the build  
Then `ninja -C build` to build it   
And finally `sudo ninja -C build install` to install it (May be different on Windows)  

## Licensing
__Raylib__  
Raylib is Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)   
and Licensed under __The ZLib license__   
More info on the license, can be found at [LICENSE.RAYLIB](/LICENSE.RAYLIB)  
  
__Main Application__  
__FULL LICENSE AT [LICENSE](/LICENSE)__  
Wdboyes13's CHIP-8 Emulator, is licensed under the GNU General Public License v3.  
See https://weelam.ca/license/ (Or [License](/LICENSE))for license information.  
SPDX-License-Identifier: GPL-3.0-or-later  