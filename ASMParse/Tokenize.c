#include <stdlib.h>
#include <string.h>
#include "Tokenize.h"

int Tokenize(const char *line, char *argv[]) {
    int argc = 0;
    char *copy = strdup(line); // Make a mutable copy
    char *token = strtok(copy, " ,\t\n");

    while (token && argc < MAX_TOKENS) {
        argv[argc++] = token;
        token = strtok(NULL, " ,\t\n");
    }

    argv[argc] = NULL; // Null-terminate like real argv
    return argc;
}