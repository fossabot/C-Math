#include "riemannSumAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

double riemannSum(const char *expression, double a, double b, unsigned int n, int options, int mode) {
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
     * options       which point of sub-interval to use  {0: left point, 1: right point, 2: mid point}
     * mode          show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check mode and options value
    if ((mode != 0 && mode != 1) || (options != 0 && options != 1 && options != 2)){
        printf("\nError: arguments option or mode are not valid\n");
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
    double area = 0, x, height;
    // coefficient is also width of every rectangle
    double coefficient = (b - a) / n;
    unsigned int scale = (options == 1) ? 1 : 0;

    // loop for summing f(a + i * coefficient)
    // if left point selected we must calculate for 0 <= i <= n - 1
    // if right point selected we must calculate for 1 <= i <= n
    // if mid point selected we have to calculate a + coefficient * (2i+1)/2 for 0 <= i <= n - 1
    for (unsigned int i = scale; i <= n - 1 + scale; ++i) {
        if (options != 2) {
            x = a + i * coefficient;
        } else {
            x = a + coefficient * (2 * i + 1) / 2;
        } // end of option if else

        // calculate height of rectangle and add it to area
        height = function_1_arg(expression, x);
        area += height;

        // show process
        if (mode) {
            printf("Height of rectangle [#%d]: %lf, heights sum =  %lf\n", i, height, area);
        } // end of if mode
    } // end of for loop

    // show process
    if (mode) {
        printf("area = height sum * width => area = %lf * %lf\n", area, coefficient);
    } // end of if mode

    // multiply sums to coefficient to get area
    // based on formula: area = (constant width) * (sum of heights)
    area *= coefficient;
    return area;
} // end of riemann sum function
