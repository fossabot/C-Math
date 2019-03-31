#ifndef C_MATH_UTIL_H
#define C_MATH_UTIL_H

#include <stdlib.h>

// common swap functions
void swapSizeT(size_t *a, size_t *b);

void swapSInt(short int *a, short int *b);

void swapInt(int *a, int *b);

void swapLInt(long int *a, long int *b);

void swapFloat(float *a, float *b);

void swapDouble(double *a, double *b);


// exit function for c-math
void Exit(int exitCode);

#endif //C_MATH_UTIL_H
