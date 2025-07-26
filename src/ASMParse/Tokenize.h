//===------- Tokenize.h - Tokenization Function Header - C Header -------------------*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#pragma once

#define MAX_TOKENS 10

int Tokenize(const char *line, char *argv[]) ;