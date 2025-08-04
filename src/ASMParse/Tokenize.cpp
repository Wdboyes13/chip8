//===------- Tokenize.c - Function to Tokenize a Loaded Assembly File ---------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#include "Tokenize.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

std::vector<std::string> SplitBySpace(const std::string& input) {
    std::string cleaned = input;

    // Replace commas with spaces
    std::replace(cleaned.begin(), cleaned.end(), ',', ' ');

    std::vector<std::string> result;
    std::istringstream iss(cleaned);
    std::string token;

    while (iss >> token) {
        result.push_back(token);
    }

    return result;
}