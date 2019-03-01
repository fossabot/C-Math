#include "rombergAlgorithm.h"
#include "trapezoidRuleAlgorithm.h"
#include "../Util/dynamicArrayLib.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double romberg(const char *expression, double a, double b, unsigned int k, double tol, int verbose, int *state) {

    // fix interval reverse
    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("Error: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check k to be more than zero
    // this is implemented to prevent divide by zero error
    if (k < 0) {
        printf("Error: argument k must be positive!\n");
        Exit(EXIT_FAILURE);
    } // end of k check

    // check error thresholds
    if (tol <= 0) {
        printf("\nError: tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    const unsigned int no_verbose = 0;
    unsigned int i, j, arraySize, index;
    double n, integral, trapezoid, result;

    for (i = 1, arraySize = 0; i <= k + 1; ++i) {
        arraySize += arraySize + i;
    }

    ArrayDouble romberg;
    initArrayDouble(&romberg, arraySize);


    for (i = 0; i <= k; ++i) {

        n = pow(2, i);
        trapezoid = trapezoidRule(expression, a, b, (unsigned int) n, no_verbose);
        insertToArrayDouble(&romberg, trapezoid);

        for (j = 1; j <= i; ++j) {
            index = romberg.next - 1;
            integral = (romberg.array[index] * pow(4, i) - romberg.array[index - 1]) / (pow(4, i) - 1);
            insertToArrayDouble(&romberg, integral);
        }
    }

    result = romberg.array[romberg.next - 1];
    freeArrayDouble(&romberg);
    return result;
}