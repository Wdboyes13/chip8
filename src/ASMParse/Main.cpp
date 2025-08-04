//===------- Main.c - Main Assembler - C --------------------------------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#include <stdio.h>
#include <iostream>
#include "Tokenize.h"
#include <stdlib.h>
#include <fstream>
#include <string>

#define FMT_INST(INST) "\"" INST "\\r\\n\",\n"
class FileClass {
public:
    void APIN(const std::string& arg1) {
        char buffer[256];
        std::snprintf(buffer, sizeof(buffer), arg1.c_str());
        std::string inst(buffer);
        out.append(inst);

    }
    void APIN(const std::string& arg1, int arg2) {
        char buffer[256];
        std::snprintf(buffer, sizeof(buffer), arg1.c_str(), arg2);
        std::string inst(buffer);
        out.append(inst);
    }
    void APIN(const std::string& arg1, int arg2, int arg3) {
        char buffer[256];
        std::snprintf(buffer, sizeof(buffer), arg1.c_str(), arg2, arg3);
        std::string inst(buffer);
        out.append(inst);
    }
    void APIN(const std::string& arg1, int arg2, int arg3, int arg4) {
        char buffer[256];
        std::snprintf(buffer, sizeof(buffer), arg1.c_str(), arg2, arg3, arg4);
        std::string inst(buffer);
        out.append(inst);
    }
    FileClass(char* argv[]) : ofile(argv[2]) {
        if (!this->ofile.is_open()) {
            std::cerr << "Failed to open output file!\n";
            return;
        }
    }
    void DONE() {
        std::cout << "Writing" << std::endl << out << std::endl;
        ofile.write(out.c_str(), out.size());
        ofile.flush();
        ofile.close();
        std::cout << "DONE" << std::endl;
    }
private:
    std::ofstream ofile;
    std::string out;
};


int hex_char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1; // Invalid hex character
}

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Usage: %s <filename> <output>\n", argv[0]);
        return 1;
    }

    std::ifstream f(argv[1]);
    FileClass* oot = new FileClass(argv);
    std::string str;
    while (std::getline(f, str)){
        if (str.empty()) continue;
        auto cargv = SplitBySpace(str);
        std::cout << str << std::endl;
        if (cargv.at(0) == "cls"){

            oot->APIN("00E0\r\n");

        } else if (cargv.at(0) == "imov"){
            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            char *end;
            int numto = (int)strtol(cargv.at(2).c_str(), &end, 0);
            oot->APIN("6%x%02x\r\n", reg, numto);

        } else if (cargv.at(0) == "ichar"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x29\r\n", reg);

        } else if (cargv.at(0) == "drw"){

            // drw VX, VY, N - DXYN
            int numx = hex_char_to_int(cargv.at(1).at(1));
            int numy = hex_char_to_int(cargv.at(2).at(1));;
            char *end;
            int numto = static_cast<int>(strtol(cargv.at(3).c_str(), &end, 0));

            oot->APIN("D%1x%1x%1x\r\n", numx, numy, numto);

        } else if (cargv.at(0) == "iadd"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            char *end;
            int numto = static_cast<int>(strtol(cargv.at(2).c_str(), &end, 0));
            oot->APIN("7%1x%02x\r\n", reg, numto);

        } else if (cargv.at(0) == "setidx"){

            int num = hex_char_to_int(cargv.at(1).at(1));
            oot->APIN("A%03x\r\n", num);

        } else if (cargv.at(0) == "rand"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            char *end;
            int numto = static_cast<int>(strtol(cargv.at(2).c_str(), &end, 0));
            oot->APIN("C%1x%02x\r\n", reg, numto);

        } else if (cargv.at(0) == "jmp"){

            char *end;
            int num = static_cast<int>(strtol(cargv.at(1).c_str(), &end, 0));
            oot->APIN("1%03x\r\n", num);

        } else if (cargv.at(0) == "ret"){

            oot->APIN("00EE\r\n");

        } else if (cargv.at(0) == "call"){

            char *end;
            int num = static_cast<int>(strtol(cargv.at(1).c_str(), &end, 0));
            oot->APIN("2%03x\r\n", num);

        } else if (cargv.at(0) == "ocall"){

            char *end;
            int num = static_cast<int>(strtol(cargv.at(1).c_str(), &end, 0));
            oot->APIN("B%03x\r\n", num);

        } else if (cargv.at(0) =="ipc.ie"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            char *end;
            int numto = (int)strtol(cargv.at(2).c_str(), &end, 0);
            oot->APIN("3%1x%02x\r\n", reg, numto);

        } else if (cargv.at(0) =="ipc.ine"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            char *end;
            int numto = (int)strtol(cargv.at(2).c_str(), &end, 0);
            oot->APIN("4%1x%02x\r\n", reg, numto);

        } else if (cargv.at(0) == "ipc.e"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("5%1x%1x0\r\n", regx, regy);

        } else if (cargv.at(0) == "ipc.ne"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("9%1x%1x0\r\n", regx, regy);

        } else if (cargv.at(0) == "pusha"){

            oot->APIN("FX55\r\n");

        } else if (cargv.at(0) == "popa"){

            oot->APIN("FX65\r\n");

        } else if (cargv.at(0) == "tm.gd"){
            
            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x07\r\n", reg);

        } else if (cargv.at(0) == "tm.sd"){
            
            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x15\r\n", reg);

        } else if (cargv.at(0) == "tm.ss"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x18\r\n", reg);

        } else if (cargv.at(0) == "idxadd"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x1E\r\n", reg);

        } else if (cargv.at(0) == "gkey"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x0A\r\n", reg);

        } else if (cargv.at(0) == "bcd"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("F%1x33\r\n", reg);

        } else if (cargv.at(0) == "del"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("D%1xF0\r\n", reg);

        } else if (cargv.at(0) == "in.p"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("E%1x9A\r\n", reg);

        } else if (cargv.at(0) == "in.np"){

            const std::string& regc = cargv.at(1);
            int reg = hex_char_to_int(regc.at(1));
            oot->APIN("E%1xA1\r\n", reg);

        } else if (cargv.at(0) == "mov"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x0\r\n", regx, regy);

        } else if (cargv.at(0) == "r.or"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x1\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.and"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x2\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.xor"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x3\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.add"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x4\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.lsub"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x5\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.rsub"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x7\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.bsr"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1x6\r\n", regx, regy);
            
        } else if (cargv.at(0) == "r.bsl"){

            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("8%1x%1xE\r\n", regx, regy);
            
        } else if (cargv.at(0) == "flp"){
            int regx = hex_char_to_int(cargv.at(1).at(1));
            int regy = hex_char_to_int(cargv.at(2).at(1));
            oot->APIN("01%1x%1x", regx, regy);
        }
    }
    oot->DONE();
    return 0;
}