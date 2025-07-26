//===------- test.c - Old tests, no longer used - C ----------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------===//
#define CLPC(HEX_LET_DEX) "00E0\r\n61" HEX_LET_DEX "\r\nF129\r\nD555\r\n"

char alphexec[] =
// A-Z
CLPC("00") // A
CLPC("01") // B
CLPC("02") // C
CLPC("03") // D
CLPC("04") // E
CLPC("05") // F
CLPC("06") // G
CLPC("07") // H
CLPC("08") // I
CLPC("09") // J
CLPC("0A") // K
CLPC("0B") // L
CLPC("0C") // M
CLPC("0D") // N
CLPC("0E") // O
CLPC("0F") // P
CLPC("10") // Q
CLPC("11") // R
CLPC("12") // S
CLPC("13") // T
CLPC("14") // U
CLPC("15") // V
CLPC("16") // W
CLPC("17") // X
CLPC("18") // Y
CLPC("19") // Z
CLPC("1A") // Some letter i forgor
// 0-9
CLPC("1B") // 0
CLPC("1C") // 1
CLPC("1D") // 2
CLPC("1E") // 3
CLPC("1F") // 4
CLPC("20") // 5
CLPC("21") // 6
CLPC("22") // 7
CLPC("23") // 8
CLPC("24") // 9
;

char exec[] = 
"F10A\r\n" // Get key - Store in V1
"6602\r\n" // Set V6 to 0x02
"D6F0\r\n"
"F20A\r\n" // Get key - Store in V2
"8124\r\n" // Put V1 + V2 in V1
"631A\r\n" // Set V3 to 26
"8314\r\n" // Put V3 + V1 in V3
"00E0\r\n" // Clear Screen
"F329\r\n" // Set I to address if char index stored in V3
"6500\r\n" // Set V5 to 0x00
"D555\r\n" // Print that
;