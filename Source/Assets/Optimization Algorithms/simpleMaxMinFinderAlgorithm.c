#include "simpleMaxMinFinderAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

double *simpleMaxMinFinder(const char *expression, double a, double b, unsigned int n) {
    /*
     * this function will find global maximum and minimum of a function in interval [a, b]
     * through sampling y = f(x) and comparing it with previous values
     *
     * ARGUMENTS:
     * expressions   the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     *
     * RETURN:       a pointer to a double array of size 2
     *               this array contains x where maximum
     *               and minimum of function occurs
     *               result[0] = maximum
     *               result[1] = minimum
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of n check

    // initializing variables
    static double results[2];
    double coefficient = (b - a) / n;
    // arbitrary value for max and min
    double x, y, max = b, min = a;
    // arbitrary value for fmax and fmin at start of program
    double fmax = function_1_arg(expression, b), fmin = fmax;

    for (unsigned int i = 0; i <= n; ++i) {
        // new x sample at interval
        x = a + coefficient * i;
        y = function_1_arg(expression, x);

        // compare y with fmax, fmin and then update
        if (y > fmax) {
            fmax = y;
            max = x;
        } else if (y < fmin) {
            fmin = y;
            min = x;
        }
    }
    // assign values to array
    results[0] = max;
    results[1] = min;
    return results;
} // end of simpleMaxMinFinder