
#define CLPC(HEX_LET_DEX) "00E0\r\n61" HEX_LET_DEX "\r\nF129\r\nD555\r\n"

char exec[] =
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