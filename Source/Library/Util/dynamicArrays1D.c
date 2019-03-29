#include "dynamicArrays1D.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initArrayLongInt(ArrayLongInt *array, size_t initialSize) {
    /*
     * This function will create an array of type "LongInt"
     * and size of  "initialSize" if it's possible.
     * it will return ARRAY_SUCCESSFULL AND ARRAY_FAILURE
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * initialSize    size of array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize memory pointer and map pointer
    long int *long_int_pointer = NULL;
    char *map_pointer = NULL;

    // size_t overflow protection
    if (initialSize > (size_t) SIZE_MAX / sizeof(long_int_pointer)) {
        printf("Error: array initialize size overflow!\n");
        // return failure
        return ARRAY_FAILURE;
    }

    // allocate memory to array and map
    long_int_pointer = (long int *) malloc(initialSize * sizeof(long_int_pointer));
    map_pointer = (char *) malloc(initialSize * sizeof(map_pointer));

    // check if memory allocated or not
    if (long_int_pointer == NULL || map_pointer == NULL) {
        printf("Error: unable to allocate memory!\n");
        // free memory
        free(long_int_pointer);
        free(map_pointer);
        // return failure
        return ARRAY_FAILURE;
    }

    // set all map elements to '0' [means emtpy]
    memset(map_pointer, '0', sizeof(*map_pointer));

    // set array parameters
    array->array = long_int_pointer;
    array->next = 0;
    array->used = 0;
    array->map = map_pointer;
    array->size = initialSize;

    return ARRAY_SUCCESSFUL;
} // end of initArrayLongInt

int extendArrayLongInt(ArrayLongInt *array, size_t extendSize) {
    /*
     * This function will reallocate memory to array and it's map
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * extendSize     size increment
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize memory pointer and map pointer
    long int *long_int_pointer = NULL;
    char *map_pointer = NULL;

    // calculate new size for array
    size_t new_size = array->size + extendSize;

    // size_t overflow protection
    if (new_size < array->size || new_size > (size_t) SIZE_MAX / sizeof(long_int_pointer)) {
        printf("Error: array extend size overflow!\n");
        return ARRAY_FAILURE;
    } // end of if

    // reallocate memory for array and map
    long_int_pointer = (long int *) realloc(array->array, new_size * sizeof(long_int_pointer));
    map_pointer = (char *) realloc(array->map, new_size * sizeof(map_pointer));

    // check if memory reallocated or not
    if (long_int_pointer == NULL || map_pointer == NULL) {
        printf("Error: unable to reallocate memory!\n");
        // free memory
        free(long_int_pointer);
        free(map_pointer);
        // return failure
        return ARRAY_FAILURE;
    } // end if

    // set new map elements to '0' [means emtpy]
    for (size_t i = array->size; i < new_size; ++i) {
        array->map[i] = '0';
    } // end of for loop

    // set array parameters
    array->array = long_int_pointer;
    array->map = map_pointer;
    array->size = new_size;

    return ARRAY_SUCCESSFUL;
} // end of extendArrayLongInt function

int initValueArrayLongInt(ArrayLongInt *array, size_t initialSize, long int element) {
    /*
     * This function will create an array of type "LongInt"
     * and size of  "initialSize" if it's possible, then it
     * will fill the array with element.
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * initialSize    size of array
     * element        element to fill all the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // init array
    int state = initArrayLongInt(array, initialSize);

    // check if memory has been allocated
    if (state == ARRAY_SUCCESSFUL) {
        // fill entire array with element
        state = fillArrayLongInt(array, 0, initialSize, element);
    } // end of if

    return state;
} // end of initValueArrayLongInt function


int fillArrayLongInt(ArrayLongInt *array, size_t start, size_t end, long int element) {
    /*
     * This function will fill array with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * it will update "map" and "used" parameters
     * it may update "next" parameter
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * start          starting index (inclusive)
     * end            ending index (exclusive)
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    if (start < 0 || end > array->size) {
        printf("Error: fillArrayLongInt bracketing \"start\" or \"end\" is wrong.\n");
        return ARRAY_FAILURE;
    } // end of if

    // fill the array
    for (size_t i = start; i < end; ++i) {
        // assign element to array
        array->array[i] = element;

        // update array parameters
        if (array->map[i] == '0') {
            // element has been assigned to an empty slot in array,
            // so update the map and +1 to used slots
            array->map[i] = '1';
            array->used++;
        } // end of if
    } // end of filler "for" loop

    // update "next" parameter of array
    if (start <= array->next) {
        // 0 is empty, 1 is data existing in the array, 2 is fill data
        // before fill
        // 111111111111111111111111110000000000000000000111111111111
        //          ^                ^              ^
        //        start         array->next        end
        //
        // after fill
        // 111111111222222222222222222222222222222220000111111111111
        //                                          ^
        //                                     array->next
        array->next = end;
    } // end of if

    return ARRAY_SUCCESSFUL;
} //end of fillArrayLongInt function

int addNextToArrayLongInt(ArrayLongInt *array, long int element) {
    /*
     * This function will insert an "element" into array at index = array->next
     * function will extend array in case of array->size == array->used
     * it will update "map" and "used" and "next" parameters
     * it may update "size" parameter
     *
     * array->next will be updated in a manner that it points to the
     * next EMPTY slot in the array
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize variables
    int state = ARRAY_SUCCESSFUL;
    size_t index = array->next;

    // extend array size if needed
    if (array->used == array->size) {
        state = extendArrayLongInt(array, array->size);
        // catch failure
        if (state == ARRAY_FAILURE) {
            return state;
        } // end of if
    } // end of if

    // add element
    array->array[index] = element;

    // update "map" and "used"
    array->map[index] = '1';
    array->used++;

    // update "next" until map[next] == '0'
    while (index < array->size && array->map[index] == '1') {
        array->next = ++index;
    } // end of while

    return state;
} // end of addNextToArrayLongInt function

int addByIndexToArrayLongInt(ArrayLongInt *array, size_t index, long int element) {
    /*
     * This function will insert an "element" into array at "index"
     * function WON'T increase array size!
     * it may update "map" and "used" and "next" parameters
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // check array bounds
    if (index >= array->size || index < 0) {
        printf("Error: wrong index!\n");
        return ARRAY_FAILURE;
    } // end of if

    // insert element
    if (index == array->next) {
        // use built-in function
        addNextToArrayLongInt(array, element);

    } else {
        // assign element
        array->array[index] = element;

        if (index > array->next) {
            // update "map" and "used"
            array->map[index] = '1';
            array->used++;
        } // end of if
    } // end of if

    return ARRAY_SUCCESSFUL;
} // end of addByIndexToArrayLongInt function

void freeArrayLongInt(ArrayLongInt *array) {
    /*
     * This function will free an array and reset it's parameters
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     *
     */

    // free memory
    free(array->array);
    free(array->map);

    // reset array parameters
    array->array = NULL;
    array->map = NULL;
    array->next = array->used = array->size = 0;
} // end of freeArrayLongInt

int initArrayDouble(ArrayDouble *array, size_t initialSize) {

    /*
     * This function will create an array of type "Double"
     * and size of  "initialSize" if it's possible.
     * it will return ARRAY_SUCCESSFULL AND ARRAY_FAILURE
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * initialSize    size of array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize memory pointer and map pointer
    double *double_pointer = NULL;
    char *map_pointer = NULL;

    // size_t overflow protection
    if (initialSize > (size_t) SIZE_MAX / sizeof(double_pointer)) {
        printf("Error: array initialize size overflow!\n");
        // return failure
        return ARRAY_FAILURE;
    }

    // allocate memory to array and map
    double_pointer = (double *) malloc(initialSize * sizeof(double_pointer));
    map_pointer = (char *) malloc(initialSize * sizeof(map_pointer));

    // check if memory allocated or not
    if (double_pointer == NULL || map_pointer == NULL) {
        printf("Error: unable to allocate memory!\n");
        // free memory
        free(double_pointer);
        free(map_pointer);
        // return failure
        return ARRAY_FAILURE;
    }

    // set all map elements to '0' [means emtpy]
    memset(map_pointer, '0', sizeof(*map_pointer));

    // set array parameters
    array->array = double_pointer;
    array->next = 0;
    array->used = 0;
    array->map = map_pointer;
    array->size = initialSize;

    return ARRAY_SUCCESSFUL;
} // end of initArrayDouble

int extendArrayDouble(ArrayDouble *array, size_t extendSize) {
    /*
     * This function will reallocate memory to array and it's map
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * extendSize     size increment
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize memory pointer and map pointer
    double *double_pointer = NULL;
    char *map_pointer = NULL;

    // calculate new size for array
    size_t new_size = array->size + extendSize;

    // size_t overflow protection
    if (new_size < array->size || new_size > (size_t) SIZE_MAX / sizeof(double_pointer)) {
        printf("Error: array extend size overflow!\n");
        return ARRAY_FAILURE;
    } // end of if

    // reallocate memory for array and map
    double_pointer = (double *) realloc(array->array, new_size * sizeof(double_pointer));
    map_pointer = (char *) realloc(array->map, new_size * sizeof(*map_pointer));

    // check if memory reallocated or not
    if (double_pointer == NULL || map_pointer == NULL) {
        printf("Error: unable to reallocate memory!\n");
        // free memory
        free(double_pointer);
        free(map_pointer);
        // return failure
        return ARRAY_FAILURE;
    } // end if

    // set new map elements to '0' [means emtpy]
    for (size_t i = array->size; i < new_size; ++i) {
        array->map[i] = '0';
    } // end of for loop

    // set array parameters
    array->array = double_pointer;
    array->map = map_pointer;
    array->size = new_size;

    return ARRAY_SUCCESSFUL;
} // end of extendArrayDouble function

int initValueArrayDouble(ArrayDouble *array, size_t initialSize, double element) {

    /*
     * This function will create an array of type "LongDouble"
     * and size of  "initialSize" if it's possible, then it
     * will fill the array with element.
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * initialSize    size of array
     * element        element to fill all the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // init array
    int state = initArrayDouble(array, initialSize);

    // check if memory has been allocated
    if (state == ARRAY_SUCCESSFUL) {
        // fill entire array with element
        state = fillArrayDouble(array, 0, initialSize, element);
    } // end of if

    return state;
} // end of initValueArrayDouble function

int fillArrayDouble(ArrayDouble *array, size_t start, size_t end, double element) {
    /*
     * This function will fill array with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * it will update "map" and "used" parameters
     * it may update "next" parameter
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * start          starting index (inclusive)
     * end            ending index (exclusive)
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    if (start < 0 || end > array->size) {
        printf("Error: fillArrayDouble bracketing \"start\" or \"end\" is wrong.\n");
        return ARRAY_FAILURE;
    } // end of if

    // fill the array
    for (size_t i = start; i < end; ++i) {
        // assign element to array
        array->array[i] = element;

        // update array parameters
        if (array->map[i] == '0') {
            // element has been assigned to an empty slot in array,
            // so update the map and +1 to used slots
            array->map[i] = '1';
            array->used++;
        } // end of if
    } // end of filler "for" loop

    // update "next" parameter of array
    if (start <= array->next) {
        // 0 is empty, 1 is data existing in the array, 2 is fill data
        // before fill
        // 111111111111111111111111110000000000000000000111111111111
        //          ^                ^              ^
        //        start         array->next        end
        //
        // after fill
        // 111111111222222222222222222222222222222220000111111111111
        //                                          ^
        //                                     array->next
        array->next = end;
    } // end of if

    return ARRAY_SUCCESSFUL;
} //end of fillArrayDouble function

int addNextToArrayDouble(ArrayDouble *array, double element) {
/*
     * This function will insert an "element" into array at index = array->next
     * function will extend array in case of array->size == array->used
     * it will update "map" and "used" and "next" parameters
     * it may update "size" parameter
     *
     * array->next will be updated in a manner that it points to the
     * next EMPTY slot in the array
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize variables
    int state = ARRAY_SUCCESSFUL;
    size_t index = array->next;

    // extend array size if needed
    if (array->used == array->size) {
        state = extendArrayDouble(array, array->size);
        // catch failure
        if (state == ARRAY_FAILURE) {
            return state;
        } // end of if
    } // end of if

    // add element
    array->array[index] = element;

    // update "map" and "used"
    array->map[index] = '1';
    array->used++;

    // update "next" until map[next] == '0'
    while (index < array->size && array->map[index] == '1') {
        array->next = ++index;
    } // end of while

    return state;
} // end of addNextToArrayDouble function

int addByIndexToArrayDouble(ArrayDouble *array, size_t index, long int element) {
    /*
     * This function will insert an "element" into array at "index"
     * function WON'T increase array size!
     * it may update "map" and "used" and "next" parameters
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     * element        element to fill the array
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // check array bounds
    if (index >= array->size || index < 0) {
        printf("Error: wrong index!\n");
        return ARRAY_FAILURE;
    } // end of if

    // insert element
    if (index == array->next) {
        // use built-in function
        addNextToArrayDouble(array, element);

    } else {
        // assign element
        array->array[index] = element;

        if (index > array->next) {
            // update "map" and "used"
            array->map[index] = '1';
            array->used++;
        } // end of if
    } // end of if

    return ARRAY_SUCCESSFUL;
} // end of addByIndexToArrayDouble function

void freeArrayDouble(ArrayDouble *array) {
    /*
     * This function will free an array and reset it's parameters
     *
     * ARGUMENTS:
     * ArrayDouble    pointer to array variable
     *
     */

    // free memory
    free(array->array);
    free(array->map);

    // reset array parameters
    array->array = NULL;
    array->map = NULL;
    array->next = array->used = array->size = 0;
} // end of freeArrayDouble