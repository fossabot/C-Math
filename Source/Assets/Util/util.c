#include "util.h"

#include <stdio.h>
#include <stdlib.h>

// a macro to swap any type,
// care must be taken while using this macro
#define swap(a, b) {a = a + b; b = a - b; a = a - b}

void swapDouble(double *a, double *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swap function

void Exit(int exitCode) {
    printf("\nPress any key to exit ...\n");
    getc(stdin);
    exit(exitCode);
} // end of Exit function
