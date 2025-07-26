#pragma once

#include <stdio.h>

FILE* LdFile(const char* name);
const char* RdLine(FILE* file);
int CLines(const char *filename);