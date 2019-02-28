#include "trapezoidRuleAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

double trapezoidRule(const char *expression, double a, double b, unsigned int n, double previous, int verbose) {
    /*
     * In mathematics, and more specifically in numerical analysis, the trapezoidal rule
     * (also known as the trapezoid rule or trapezium rule) is a technique for approximating the definite integral.
     *
     * ARGUMENTS:
     * expressions   the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     * previous      use previous integral in calculation
     * verbose       show process {0: no, 1: yes}
     *
     */


    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of n check

    // initializing variables
    double area = 0, x;
    // coefficient is also width of every trapezoid
    double coefficient = (b - a) / n;

    // according to formula: width/2 * (f(x0) + f(xn) + 2 * sigma(f(xi)))
    // first we calculate f(x0) + f(xn)
    area += function_1_arg(expression, a) + function_1_arg(expression, b);

    // calculate sigma part
    for (unsigned int i = 1; i < n; ++i) {
        x = a + i * coefficient;
        area += 2 * function_1_arg(expression, x);
        // show process
        if (verbose) {
            printf("[#%d] Heights sum =  %lf .\n", i, area);
        } // end of if verbose
    } // end of for loop

    // show process
    if (verbose) {
        printf("area = (h / 2) * heights sum => area = (%lf) * %lf .\n", coefficient / 2, area);
    } // end of if verbose

    // multiply sums to width/2
    area *= coefficient / 2;
    // add previous integral to final result
    area += previous / 2;

    return area;
} // end of riemann sum function
