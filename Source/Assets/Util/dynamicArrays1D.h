#ifndef C_MATH_DYNAMICARRAYS1D_H
#define C_MATH_DYNAMICARRAYS1D_H

#include <stdlib.h>
#include <limits.h>

#ifndef SIZE_MAX
# ifdef __SIZE_MAX__
#  define SIZE_MAX __SIZE_MAX__
# endif
#endif

#define ARRAY_SUCCESSFUL 1
#define ARRAY_FAILURE 0

#define I_EMPTY '0'
#define I_FILLED '1'

#define T_CHAR 1
#define T_SINT 2
#define T_INT 3
#define T_LINT 4
#define T_FLOAT 5
#define T_DOUBLE 6

typedef union {
    char *pChar;
    short int *pShortInt;
    int *pInt;
    long int *pLongInt;
    float *pFloat;
    double *pDouble;
} Array_Type;

typedef struct {
    char *map;
    Array_Type array;
    size_t type;
    size_t next;
    size_t used;
    size_t size;
} Array1D;

int initArray1D(Array1D *array, size_t initialSize, size_t type);

int extendSizeArray1D(Array1D *array, size_t extendSize);

int initValueArray1D(Array1D *array, size_t initialSize, size_t type, void *element);

int fillArray1D(Array1D *array, size_t start, size_t step, size_t end, void *element);

int addNextToArray1D(Array1D *array, void *element);

int addByIndexArray1D(Array1D *array, size_t index, void *element);

void freeArray1D(Array1D *array);

void __arrayUpdaterArray1D(Array1D *array, size_t index, void *element);

void __nextUpdaterArray1D(Array1D *array);

char getElementCharArray1D(Array1D *array, size_t index);

short int getElementSIntArray1D(Array1D *array, size_t index);

int getElementIntArray1D(Array1D *array, size_t index);

long int getElementLIntArray1D(Array1D *array, size_t index);

float getElementFloatArray1D(Array1D *array, size_t index);

double getElementDoubleArray1D(Array1D *array, size_t index);

#endif //C_MATH_DYNAMICARRAYS1D_H
