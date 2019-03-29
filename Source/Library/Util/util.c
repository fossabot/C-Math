#include "util.h"

#include <stdio.h>

// common swap functions
void swapSizeT(size_t *a, size_t *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapSizeT function

void swapSInt(short int *a, short int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapSInt function

void swapInt(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapInt function

void swapLInt(long int *a, long int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapLint function

void swapFloat(float *a, float *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapFloat function

void swapDouble(double *a, double *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
} // end of swapDouble function

// exit function for c-math
void Exit(int exitCode) {
    /*
     * This function's jop is to prevent instant terminal exit
     * it will ask user to press any key and then will exit
     * the program with the exit code provided by caller function
     */
    printf("\nPress any key to exit ...\n");
    getc(stdin);
    exit(exitCode);
} // end of Exit function
