//===------- LoadFile.h - Assembly file loader, and read functions header - C Header --*-===//
//
// Copyright (C) 2025 Wdboyes13
// Part of Wdboyes13's CHIP-8 Emulator Assembler, under the GNU General Public License v3.
// See https://weelam.ca/license/ for license information.
// SPDX-License-Identifier: GPL-3.0-or-later
//
//===----------------------------------------------------------------------------------===//
#pragma once

#include <stdio.h>

FILE* LdFile(const char* name);
const char* RdLine(FILE* file);
int CLines(const char *filename);