#include "rombergAlgorithm.h"
#include "trapezoidRuleAlgorithm.h"
#include "../Util/dynamicArrays1D.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double romberg(const char *expression, double a, double b, unsigned int k, double tol, int verbose) {

    /*
     * In numerical analysis, Romberg's method is used to estimate the definite integral
     * by applying Richardson extrapolation repeatedly on the trapezium rule or
     * the rectangle rule. The estimates generate a triangular array. Romberg's method is
     * a Newton–Cotes formula – it evaluates the integrand at equally spaced points.
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * k             degree of integration
     * tol           tolerance error
     * verbose       show process {0: no, 1: yes}
     *
     */

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // fix interval reverse
    if (a > b) {
        swapDouble(&a, &b);
    } // end of if

    // check k to be more than zero
    if (k < 0) {
        printf("\nError: argument k must be positive!\n");
        Exit(EXIT_FAILURE);
    } // end of k check

    // check error thresholds
    if (tol < 0) {
        printf("\nError: tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initializing variables
    const unsigned int no_verbose = 0;
    unsigned int i, j, l, arraySize;
    double n, integral, trapezoid, error;
    double previous_result = 0, result = 0;
    size_t index;

    // determine array size
    // example (k = 3):
    //
    // k = 0               |
    // k = 1              | |
    // k = 2             | | |
    // k = 3            | | | |
    //
    // as you can see for k = 3 we need an array of size 10 to store all romberg results
    // for calculating the size of array, I came with this solution by myself, if you know
    // a better (faster) answer, please commit a pull request. thank you!
    for (i = 1, arraySize = 0; i <= k + 1; ++i) {
        arraySize += i;
    }

    // declare and initialize romberg array
    ArrayDouble romberg;
    initArrayDouble(&romberg, arraySize);

    // calculate
    for (i = 0; i <= k; ++i) {
        // get number of sub-intervals (n) for trapezoid integration
        n = pow(2, i);
        trapezoid = trapezoidRule(expression, a, b, (unsigned int) n, no_verbose);

        // add the result to the romberg table
        addNextToArrayDouble(&romberg, trapezoid);

        // romberg algorithm
        for (j = 1; j <= i; ++j) {
            index = romberg.next - 1;
            integral = (romberg.array[index] * pow(4, i) - romberg.array[index - 1]) / (pow(4, i) - 1);
            addNextToArrayDouble(&romberg, integral);
        }

        // calculate error [relative error to avoid large numbers]
        result = romberg.array[romberg.next - 1];
        error = (result - previous_result) / result;

        // Termination Criterion
        if (i != 0 && tol != 0 && tol > error) {
            // show process
            if (verbose) {
                printf("\nIn this iteration, error is less that threshold [%g < %g].\n"
                       "so integral is close enough to it's real value.\n", error, tol);
            } // end of if verbose
            break;
        } // end of termination criterion

        // replace previous result with new one for next iteration
        previous_result = result;
    }

    // show process
    if (verbose) {
        // show title
        printf("Romberg Integration Table\n");

        // print N and K
        char string[2] = "n";
        printf("%-10s", string);
        printf("k = ");

        // print k numbers based on filled array elements
        for (i = 0, j = 1, l = 0; i <= k && j <= l + 1; ++i, ++j) {

            // expected array size at this step
            l += j;

            // compare used space with expected size
            if (l > romberg.used) break;

            // print number
            printf("%-15d ", i);
        } // end of for loop

        // go to next line
        printf("\n");

        // print romberg array elements
        for (i = 1, index = 0; i <= k + 1 && index <= romberg.next - 1; ++i) {
            printf("%-13d", (int) pow(2, i - 1));
            for (j = 1; j <= i; ++j) {
                printf("%-+13lf", romberg.array[index++]);
                // choose right punctuation mark
                if (j == i) {
                    printf(" .\n");
                } else {
                    printf(" , ");
                } // end of if else
            }// end of inner for loop
        }// end of outer for loop
    } // end of if verbose

    // free allocated memory
    freeArrayDouble(&romberg);
    return result;
} // end of romberg function