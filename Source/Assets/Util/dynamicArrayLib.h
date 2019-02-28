#ifndef C_MATH_DYNAMICARRAYLIB_H
#define C_MATH_DYNAMICARRAYLIB_H

typedef struct {
    long int *array;
    unsigned long int used;
    unsigned long int size;
} ArrayLongInt;

void initArrayLongInt(ArrayLongInt *array, unsigned long int initialSize);

void insertToArrayLongInt(ArrayLongInt *array, long int element);

void freeArrayLongInt(ArrayLongInt *array);

typedef struct {
    double *array;
    unsigned long int used;
    unsigned long int size;
} ArrayDouble;

void initArrayDouble(ArrayDouble *array, unsigned long int initialSize);

void insertToArrayDouble(ArrayDouble *array, double element);

void freeArrayDouble(ArrayDouble *array);

#endif //C_MATH_DYNAMICARRAYLIB_H
