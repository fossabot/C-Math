#ifndef C_MATH_DYNAMICARRAYS1D_H
#define C_MATH_DYNAMICARRAYS1D_H

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
    unsigned long int next;
    unsigned long int used;
    unsigned long int size;
} ArrayDouble;

void initArrayDouble(ArrayDouble *array, unsigned long int initialSize);

void initValueArrayDouble(ArrayDouble *array, unsigned long int initialSize, double value);

void insertToArrayDouble(ArrayDouble *array, double element);

void addByIndexToArrayDouble(ArrayDouble *array, double element, unsigned long int index);

void freeArrayDouble(ArrayDouble *array);

typedef struct {
    char *array;
    unsigned long int next;
    unsigned long int used;
    unsigned long int size;
} ArrayChar;

void initArrayChar(ArrayChar *array, unsigned long int initialSize);

void initValueArrayChar(ArrayChar *array, unsigned long int initialSize, char value);

void insertToArrayChar(ArrayChar *array, char element);

void addByIndexToArrayChar(ArrayChar *array, char element, unsigned long int index);

void freeArrayChar(ArrayChar *array);

#endif //C_MATH_DYNAMICARRAYS1D_H
