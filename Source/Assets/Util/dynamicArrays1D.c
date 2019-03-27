#include "dynamicArrays1D.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int initArray1D(Array1D *array, size_t initialSize, size_t type) {
    /*
     * This function will create an array of type "type"
     * and size of  "initialSize" if it's possible.
     * it will return ARRAY_SUCCESSFULL AND ARRAY_FAILURE
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * initialSize    size of array
     * type           type of array elements
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */


    // check array type
    if (type != T_CHAR && type != T_SINT && type != T_INT && type != T_LINT && type != T_FLOAT && type != T_DOUBLE) {
        printf("\nError: array type is wrong!\n");
        return ARRAY_FAILURE;
    } // end of array type check

    // initialize map pointer
    char *map_pointer = NULL;

    // initialize memory pointer
    Array_Type array_pointer;

    // initialize error indicator
    int error_state = 0;

    // decide which type to use
    switch (type) {
        case T_CHAR:
            array_pointer.pChar = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pChar)) ? 1 : 0;
            break;

        case T_SINT:
            array_pointer.pShortInt = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pShortInt)) ? 1 : 0;
            break;

        case T_INT:
            array_pointer.pInt = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pInt)) ? 1 : 0;
            break;

        case T_LINT:
            array_pointer.pLongInt = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pLongInt)) ? 1 : 0;
            break;

        case T_FLOAT:
            array_pointer.pFloat = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pFloat)) ? 1 : 0;
            break;

        case T_DOUBLE:
            array_pointer.pDouble = NULL;
            error_state = (initialSize > (size_t) SIZE_MAX / sizeof(array_pointer.pDouble)) ? 1 : 0;
            break;
    } // end of switch

    // size_t overflow protection
    if (error_state) {
        printf("Error: array initialize size overflow!\n");
        // return failure
        return ARRAY_FAILURE;
    }

    // allocate memory to map
    map_pointer = (char *) malloc(initialSize * sizeof(map_pointer));

    // allocate memory to array
    switch (type) {
        case T_CHAR:
            array_pointer.pChar = (char *) malloc(initialSize * sizeof(array_pointer.pChar));
            error_state = (array_pointer.pChar == NULL) ? 1 : 0;
            break;

        case T_SINT:
            array_pointer.pShortInt = (short int *) malloc(initialSize * sizeof(array_pointer.pShortInt));
            error_state = (array_pointer.pShortInt == NULL) ? 1 : 0;
            break;

        case T_INT:
            array_pointer.pInt = (int *) malloc(initialSize * sizeof(array_pointer.pInt));
            error_state = (array_pointer.pInt == NULL) ? 1 : 0;
            break;

        case T_LINT:
            array_pointer.pLongInt = (long int *) malloc(initialSize * sizeof(array_pointer.pLongInt));
            error_state = (array_pointer.pLongInt == NULL) ? 1 : 0;
            break;

        case T_FLOAT:
            array_pointer.pFloat = (float *) malloc(initialSize * sizeof(array_pointer.pFloat));
            error_state = (array_pointer.pFloat == NULL) ? 1 : 0;
            break;

        case T_DOUBLE:
            array_pointer.pDouble = (double *) malloc(initialSize * sizeof(array_pointer.pDouble));
            error_state = (array_pointer.pDouble == NULL) ? 1 : 0;
            break;
    } // end of switch

    // check if memory allocated or not
    if (error_state || map_pointer == NULL) {
        printf("Error: unable to allocate memory!\n");

        // free array pointer
        switch (type) {
            case T_CHAR:
                free(array_pointer.pChar);
                break;

            case T_SINT:
                free(array_pointer.pShortInt);
                break;

            case T_INT:
                free(array_pointer.pInt);
                break;

            case T_LINT:
                free(array_pointer.pLongInt);
                break;

            case T_FLOAT:
                free(array_pointer.pFloat);
                break;

            case T_DOUBLE:
                free(array_pointer.pDouble);
                break;
        } // end of switch

        // free map pointer
        free(map_pointer);

        // return failure
        return ARRAY_FAILURE;
    } // end of if

    // set all map elements to '0' [I_EMPTY]
    memset(map_pointer, I_EMPTY, sizeof(*map_pointer));

    // set array parameters
    switch (type) {
        case T_CHAR:
            array->array.pChar = array_pointer.pChar;
            break;

        case T_SINT:
            array->array.pShortInt = array_pointer.pShortInt;
            break;

        case T_INT:
            array->array.pInt = array_pointer.pInt;
            break;

        case T_LINT:
            array->array.pLongInt = array_pointer.pLongInt;
            break;

        case T_FLOAT:
            array->array.pFloat = array_pointer.pFloat;
            break;

        case T_DOUBLE:
            array->array.pDouble = array_pointer.pDouble;
            break;
    } // end of switch

    array->map = map_pointer;
    array->type = type;
    array->next = 0;
    array->used = 0;
    array->size = initialSize;

    return ARRAY_SUCCESSFUL;
} // end of initArray1D function

int extendSizeArray1D(Array1D *array, size_t extendSize) {
    /*
     * This function will reallocate memory to array and it's map
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * extendSize     size increment
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize map pointer
    char *map_pointer = NULL;

    // initialize memory pointer
    Array_Type array_pointer;

    // initialize error indicator
    int error_state = 0;

    // calculate new size for array
    size_t new_size = array->size + extendSize;

    // size_t overflow protection
    if (new_size < array->size) {
        printf("Error: array extend size overflow! new_size exceeds SIZE_MAX.\n");
        return ARRAY_FAILURE;
    } // end of if

    // decide which type to use
    switch (array->type) {
        case T_CHAR:
            array_pointer.pChar = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pChar)) ? 1 : 0;
            break;

        case T_SINT:
            array_pointer.pShortInt = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pShortInt)) ? 1 : 0;
            break;

        case T_INT:
            array_pointer.pInt = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pInt)) ? 1 : 0;
            break;

        case T_LINT:
            array_pointer.pLongInt = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pLongInt)) ? 1 : 0;
            break;

        case T_FLOAT:
            array_pointer.pFloat = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pFloat)) ? 1 : 0;
            break;

        case T_DOUBLE:
            array_pointer.pDouble = NULL;
            error_state = (new_size > (size_t) SIZE_MAX / sizeof(array_pointer.pDouble)) ? 1 : 0;
            break;
    } // end of switch


    // size_t overflow protection
    if (error_state) {
        printf("Error: array extend size overflow! new_size > SIZE_MAX / sizeof(array_pointer.pDouble)\n");
        // return failure
        return ARRAY_FAILURE;
    }

    // allocate memory to map
    map_pointer = (char *) realloc(array->map, new_size * sizeof(map_pointer));

    // allocate memory to array
    switch (array->type) {
        case T_CHAR:
            array_pointer.pChar = (char *) realloc(array->array.pChar, new_size * sizeof(array_pointer.pChar));
            error_state = (array_pointer.pChar == NULL) ? 1 : 0;
            break;

        case T_SINT:
            array_pointer.pShortInt = (short int *) realloc(array->array.pShortInt,
                                                            new_size * sizeof(array_pointer.pShortInt));
            error_state = (array_pointer.pShortInt == NULL) ? 1 : 0;
            break;

        case T_INT:
            array_pointer.pInt = (int *) realloc(array->array.pInt, new_size * sizeof(array_pointer.pInt));
            error_state = (array_pointer.pInt == NULL) ? 1 : 0;
            break;

        case T_LINT:
            array_pointer.pLongInt = (long int *) realloc(array->array.pLongInt,
                                                          new_size * sizeof(array_pointer.pLongInt));
            error_state = (array_pointer.pLongInt == NULL) ? 1 : 0;
            break;

        case T_FLOAT:
            array_pointer.pFloat = (float *) realloc(array->array.pFloat, new_size * sizeof(array_pointer.pFloat));
            error_state = (array_pointer.pFloat == NULL) ? 1 : 0;
            break;

        case T_DOUBLE:
            array_pointer.pDouble = (double *) realloc(array->array.pDouble, new_size * sizeof(array_pointer.pDouble));
            error_state = (array_pointer.pDouble == NULL) ? 1 : 0;
            break;
    } // end of switch

    // check if memory allocated or not
    if (error_state || map_pointer == NULL) {
        printf("Error: unable to allocate memory!\n");

        // free array pointer
        switch (array->type) {
            case T_CHAR:
                free(array_pointer.pChar);
                break;

            case T_SINT:
                free(array_pointer.pShortInt);
                break;

            case T_INT:
                free(array_pointer.pInt);
                break;

            case T_LINT:
                free(array_pointer.pLongInt);
                break;

            case T_FLOAT:
                free(array_pointer.pFloat);
                break;

            case T_DOUBLE:
                free(array_pointer.pDouble);
                break;
        } // end of switch

        // free map pointer
        free(map_pointer);

        // return failure
        return ARRAY_FAILURE;
    } // end of if

    // set new map elements to '0' [I_EMPTY]
    for (size_t i = array->size; i < new_size; ++i) {
        array->map[i] = I_EMPTY;
    } // end of for loop

    // set array parameters
    switch (array->type) {
        case T_CHAR:
            array->array.pChar = array_pointer.pChar;
            break;

        case T_SINT:
            array->array.pShortInt = array_pointer.pShortInt;
            break;

        case T_INT:
            array->array.pInt = array_pointer.pInt;
            break;

        case T_LINT:
            array->array.pLongInt = array_pointer.pLongInt;
            break;

        case T_FLOAT:
            array->array.pFloat = array_pointer.pFloat;
            break;

        case T_DOUBLE:
            array->array.pDouble = array_pointer.pDouble;
            break;
    } // end of switch

    array->map = map_pointer;
    array->size = new_size;

    return ARRAY_SUCCESSFUL;
} // end of extendArray1D function

void freeArray1D(Array1D *array) {
    /*
     * This function will free an array and reset it's parameters
     *
     * ARGUMENTS:
     * array  pointer to array variable
     *
     */

    // free array pointer
    switch (array->type) {
        case T_CHAR:
            free(array->array.pChar);
            array->array.pChar = NULL;
            break;

        case T_SINT:
            free(array->array.pShortInt);
            array->array.pShortInt = NULL;
            break;

        case T_INT:
            free(array->array.pInt);
            array->array.pInt = NULL;
            break;

        case T_LINT:
            free(array->array.pLongInt);
            array->array.pLongInt = NULL;
            break;

        case T_FLOAT:
            free(array->array.pFloat);
            array->array.pFloat = NULL;
            break;

        case T_DOUBLE:
            free(array->array.pDouble);
            array->array.pDouble = NULL;
            break;
    } // end of switch

    // free map pointer
    free(array->map);
    array->map = NULL;

    // reset array parameters
    array->type = array->next = array->used = array->size = 0;

} // end of freeArray1D function

int initValueArray1D(Array1D *array, size_t initialSize, size_t type, void *element) {
    /*
     * This function will create an array of type "type"
     * and size of  "initialSize" if it's possible, then it
     * will fill the array with element.
     *
     * ARGUMENTS:
     * array           pointer to array variable
     * initialSize     size of array
     * type            type of elements
     * element         pointer to element
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // init array
    int state = initArray1D(array, initialSize, type);

    // check if memory has been allocated
    if (state == ARRAY_SUCCESSFUL) {
        // fill entire array with element
        state = fillArray1D(array, 0, 1, initialSize, element);
    } // end of if

    return state;
} // end of initValueArray1D function

int fillArray1D(Array1D *array, size_t start, size_t step, size_t end, void *element) {
    /*
     * This function will fill array with an element
     * from index (inclusive) "start" to index (exclusive) "end"
     * with step size "step"
     *
     * it will update "map" and "used" parameters
     * it may update "next" parameter
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * start          starting index (inclusive)
     * step           step size
     * end            ending index (exclusive)
     * element        pointer to element
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    if (start < 0 || end > array->size) {
        printf("Error: fillArrayLongInt bracketing \"start\" or \"end\" is wrong.\n");
        return ARRAY_FAILURE;
    } // end of if

    if (step <= 0) {
        printf("Error: step size can't be less than 1.\n");
        return ARRAY_FAILURE;
    } // end of if

    // fill the array
    for (size_t i = start; i < end; i += step) {
        // assign element to array
        __arrayUpdaterArray1D(array, i, element);

        // update array parameters
        if (array->map[i] == I_EMPTY) {
            // element has been assigned to an empty slot in array,
            // so update the map and +1 to used slots
            array->map[i] = I_FILLED;
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
        // the above case is for step = 1, if step is more than 1,
        // if (next - start) % step == 0, we can add 1 to 'next', because it will be filled.
        //
        // finally we will check next map slot to make sure it's empty and 'next' is valid
        // and we will keep adding 1 to next until map[next] == I_EMPTY.
        //
        if (step == 1) {
            array->next = end;
        } else if ((array->next - start) % step == 0) {
            array->next++;
        } // end of if

        // update "next"
        __nextUpdaterArray1D(array);
    } // end of if

    return ARRAY_SUCCESSFUL;
} //end of fillArray1D function

int addNextToArray1D(Array1D *array, void *element) {
    /*
     * This function will insert an "element" into array at index = array->next
     * function will extend size of array in case of array->size == array->used
     * it will update "map" and "used" and "next" parameters
     * it may update "size" parameter
     *
     * array->next will be updated in a manner that it points to the
     * next EMPTY slot in the array
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * element        pointer to element
     *
     * RETURN:
     * ARRAY_SUCCESSFULL
     * ARRAY_FAILURE
     */

    // initialize variables
    int state = ARRAY_SUCCESSFUL;

    // extend array size if needed
    if (array->used == array->size) {
        state = extendSizeArray1D(array, array->size);
        // catch failure
        if (state == ARRAY_FAILURE) {
            return state;
        } // end of if
    } // end of if

    // add element
    __arrayUpdaterArray1D(array, array->next, element);

    // update "map" and "used"
    array->map[array->next] = I_FILLED;
    array->used++;

    // update "next"
    __nextUpdaterArray1D(array);

    return state;
} // end of addNextToArray1D function

int addByIndexArray1D(Array1D *array, size_t index, void *element) {
    /*
     * This function will insert an "element" into array at "index"
     * function WON'T increase array size!
     * it may update "map" and "used" and "next" parameters
     *
     * ARGUMENTS:
     * ArrayLongInt   pointer to array variable
     * element        pointer to element
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
        // use addNextToArray1D function to
        // take care of everything
        int state = addNextToArray1D(array, element);

        // catch error
        if (state == ARRAY_FAILURE) {
            return state;
        } // end of catch error

    } else {

        // assign element
        __arrayUpdaterArray1D(array, index, element);

        // update array parameters
        if (index > array->next && array->map[index] == I_EMPTY) {
            // update "map" and "used" if they
            // aren't already counted for this index
            array->map[index] = I_FILLED;
            array->used++;
        } // end of if
    } // end of if

    return ARRAY_SUCCESSFUL;
} // end of addByIndexArray1D function

void __arrayUpdaterArray1D(Array1D *array, size_t index, void *element) {
    /*
     * This function purpose is to add elements
     * to array.array."array.type"[index]
     *
     * ARGUMENTS:
     * array           pointer to array variable
     */

    // choose correct updater
    switch (array->type) {
        case T_CHAR:
            array->array.pChar[index] = *((char *) element);
            break;

        case T_SINT:
            array->array.pShortInt[index] = *((short int *) element);
            break;

        case T_INT:
            array->array.pInt[index] = *((int *) element);
            break;

        case T_LINT:
            array->array.pLongInt[index] = *((long int *) element);
            break;

        case T_FLOAT:
            array->array.pFloat[index] = *((float *) element);
            break;

        case T_DOUBLE:
            array->array.pDouble[index] = *((double *) element);
            break;
    } // end of switch
} // end of __arrayUpdaterArray1D function

void __nextUpdaterArray1D(Array1D *array) {
    /*
     * This function purpose is to update
     * array.next to point to next empty [available]
     * slot in the array
     *
     * ARGUMENTS:
     * array           pointer to array variable
     */

    while (array->next < array->size && array->map[array->next] == I_FILLED) {
        array->next++;
    } // end of while
} // end of __nextUpdaterArray1D function

char getElementCharArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "char"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pChar[index];
} // end of getElementCharArray1D function

short int getElementSIntArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "short int"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pShortInt[index];
} // end of getElementSIntArray1D function

int getElementIntArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "int"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pInt[index];
} // end of getElementIntArray1D function

long int getElementLIntArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "long int"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pLongInt[index];
} // end of getElementLIntArray1D function

float getElementFloatArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "float"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pFloat[index];
} // end of getElementFloatArray1D function

double getElementDoubleArray1D(Array1D *array, size_t index) {
    /*
     * This function will get an element of type "double"
     * in the index "index" from an array.
     *
     * ARGUMENTS:
     * array          pointer to array variable
     * index          index of element
     *
     */

    return array->array.pDouble[index];
} // end of getElementDoableArray1D function