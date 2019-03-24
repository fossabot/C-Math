#ifndef C_MATH_DYNAMICARRAYS1D_H
#define C_MATH_DYNAMICARRAYS1D_H

#include <stdlib.h>

#define ARRAY_SUCCESSFUL 1
#define ARRAY_FAILURE 0

typedef struct {
    char *map;
    long int *array;
    size_t next;
    size_t used;
    size_t size;
} ArrayLongInt;

int initArrayLongInt(ArrayLongInt *array, size_t initialSize);

int extendArrayLongInt(ArrayLongInt *array, size_t extendSize);

int initValueArrayLongInt(ArrayLongInt *array, size_t initialSize, long int element);

int fillArrayLongInt(ArrayLongInt *array, size_t start, size_t end, long int element);

int addNextToArrayLongInt(ArrayLongInt *array, long int element);

int addByIndexToArrayLongInt(ArrayLongInt *array, size_t index, long int element);

void freeArrayLongInt(ArrayLongInt *array);

typedef struct {
    char *map;
    double *array;
    size_t next;
    size_t used;
    size_t size;
} ArrayDouble;

int initArrayDouble(ArrayDouble *array, size_t initialSize);

int extendArrayDouble(ArrayDouble *array, size_t extendSize);

int initValueArrayDouble(ArrayDouble *array, size_t initialSize, double element);

int fillArrayDouble(ArrayDouble *array, size_t start, size_t end, double element);

int addNextToArrayDouble(ArrayDouble *array, double element);

int addByIndexToArrayDouble(ArrayDouble *array, size_t index, long int element);

void freeArrayDouble(ArrayDouble *array);

#endif //C_MATH_DYNAMICARRAYS1D_H
