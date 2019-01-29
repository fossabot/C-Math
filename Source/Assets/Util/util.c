#include "util.h"

#include <stdio.h>

void Exit(void) {
    printf("\nPress any key to exit ...\n");
    getc(stdin);
} // end of exit