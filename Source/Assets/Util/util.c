#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void Exit(int exitCode) {
    printf("\nPress any key to exit ...\n");
    getc(stdin);
    exit(exitCode);
} // end of exit