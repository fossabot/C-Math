#include "dynamicArrays1D.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void initArrayLongInt(ArrayLongInt *array, unsigned long int initialSize) {

    long int *int_pointer;
    int_pointer = (long int *) malloc(initialSize * sizeof(int_pointer));

    if (int_pointer == NULL) {
        printf("Unable to allocate memory!\n");
        free(int_pointer);
        Exit(EXIT_FAILURE);
    } else {
        array->array = int_pointer;
        array->used = 0;
        array->size = initialSize;
    }
}

void insertToArrayLongInt(ArrayLongInt *array, long int element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used
    // only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (array->used == array->size) {

        unsigned long int new_size = array->size * 2;

        long int *int_pointer;
        int_pointer = (long int *) realloc(array->array, new_size * sizeof(int_pointer));

        if (int_pointer == NULL) {
            printf("Unable to reallocate memory!\n");
            free(int_pointer);
            Exit(EXIT_FAILURE);
        } else {
            array->size = new_size;
            array->array = int_pointer;
        }
    }
    array->array[array->used++] = element;
}

void freeArrayLongInt(ArrayLongInt *array) {
    free(array->array);
    array->array = NULL;
    array->used = array->size = 0;
}

void initArrayDouble(ArrayDouble *array, unsigned long int initialSize) {

    double *int_pointer;
    int_pointer = (double *) malloc(initialSize * sizeof(int_pointer));

    if (int_pointer == NULL) {
        printf("Unable to allocate memory!\n");
        free(int_pointer);
        Exit(EXIT_FAILURE);
    } else {
        array->array = int_pointer;
        array->next = 0;
        array->used = 0;
        array->size = initialSize;
    }
}

void initValueArrayDouble(ArrayDouble *array, unsigned long int initialSize, double value) {

    initArrayDouble(array, initialSize);

    for (int i = 0; i < initialSize; ++i) {
        insertToArrayDouble(array, value);
    }

}

void insertToArrayDouble(ArrayDouble *array, double element) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used
    // only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (array->used == array->size) {

        unsigned long int new_size = array->size * 2;

        double *int_pointer;
        int_pointer = (double *) realloc(array->array, new_size * sizeof(int_pointer));

        if (int_pointer == NULL) {
            printf("Unable to reallocate memory!\n");
            free(int_pointer);
            Exit(EXIT_FAILURE);
        } else {
            array->size = new_size;
            array->array = int_pointer;
        }
    }
    array->array[array->next++] = element;
    array->used += 1;
}

void addByIndexToArrayDouble(ArrayDouble *array, double element, unsigned long int index) {
    if (array->size - 1 < index || index < 0) {
        printf("Error: wrong index!\n");
        Exit(EXIT_FAILURE);
    }

    if (index > array->next) {
        array->array[index] = element;
        array->used += 1;
    } else if (index == array->next) {
        insertToArrayDouble(array, element);
    } else {
        array->array[index] = element;
    }
}

void freeArrayDouble(ArrayDouble *array) {
    free(array->array);
    array->array = NULL;
    array->next = array->used = array->size = 0;
}