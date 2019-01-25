#include "util.h"

#include <stdio.h>

void Exit(void) {
    printf("\nPress any key to exit ...");
    getc(stdin);
} // end of exit