#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Exit(int exitCode) {
    printf("\nPress any key to exit ...\n");
    getc(stdin);
    exit(exitCode);
} // end of exit

void strToLower(char *string) {
    strlwr(string);
}