#include "trapezoidRuleAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

double trapezoidRule(const char *expression, double a, double b, unsigned int n, int mode) {
    /*
     * In mathematics, a Riemann sum is a certain kind of approximation of an integral by a finite sum. It is named
     * after nineteenth century German mathematician Bernhard Riemann. One very common application is approximating
     * the area of functions or lines on a graph, but also the length of curves and other approximations.
     * The sum is calculated by dividing the region up into shapes (rectangles, trapezoids, parabolas, or cubic) that
     * together form a region that is similar to the region being measured, then calculating the area for each of these
     * shapes, and finally adding all of these small areas together. This approach can be used to find
     * a numerical approximation for a definite integral even if the fundamental theorem of calculus
     * does not make it easy to find a closed-form solution.
     *
     * ARGUMENTS:
     * expressions   the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use
     * mode          show process {0: no, 1: yes}
     *
     */


    // check mode and options value
    if (mode != 0 && mode != 1) {
        printf("\nError: mode argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("Error: argument n must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of ete check

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
        if (mode) {
            printf("[#%d] Heights sum =  %lf\n", i, area);
        } // end of if mode
    } // end of for loop

    // multiply sums to width/2
    area *= coefficient / 2;
    return area;
} // end of riemann sum function
