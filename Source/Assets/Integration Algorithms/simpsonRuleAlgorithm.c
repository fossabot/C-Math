#include "simpsonRuleAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>

double simpsonRule(const char *expression, double a, double b, unsigned int n, int options, int verbose) {
    /*
     * In numerical analysis, Simpson's rule is a method for numerical integration,
     * the numerical approximation of definite integrals. Specifically, it is
     * the following approximation for n equally spaced subdivisions
     *
     * ARGUMENTS:
     * expressions   the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * n             number of sub-intervals to use, better to be an even number
     * options       which point of sub-interval to use  {0: 1/3 rule, 1: 3/8 rule}
     * verbose       show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check verbose and options value
    if ((verbose != 0 && verbose != 1) || (options != 0 && options != 1)) {
        printf("\nError: arguments option or verbose are not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check n to be more than zero
    // this is implemented to prevent divide by zero error
    if (n <= 0) {
        printf("\nError: argument n must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of n check

    // initializing variables
    double area = 0, even = 0, odd = 0, cubic = 0, regular = 0, x;
    // coefficient is also width of every arc
    double coefficient = (b - a) / n;

    // according to formula: width/3 * (f(x0) + f(xn) + 2 * sigma(f(x2i)) + 4 * sigma(f(x2i-1)))
    // or 3/8 formula: 3*width/8 * (f(x0) + f(xn) + 2 * sigma(f(xi)) + 4 * sigma(f(x3i)))
    // first we calculate f(x0) + f(xn)
    area += function_1_arg(expression, a) + function_1_arg(expression, b);

    if (options == 0) {
        // use regular simpson rule, this method is based on quadratic interpolation
        // fix odd n problem, by making it even,
        // it will make result to be correct
        if (n % 2 == 1) {
            ++n;
        } // end of n correction

        // sum even sigma part
        for (unsigned int i = 1; i <= (double) n / 2 - 1; ++i) {
            x = a + 2 * i * coefficient;
            even += function_1_arg(expression, x);
            // show process
            if (verbose) {
                printf("[#%d] f(xi[i = 2k]) = %lf, sigma(f(xi[i = 2k])) =  %lf .\n",
                       2 * i, function_1_arg(expression, x), even);
            } // end of if verbose
        } // end of for loop

        // sum odd sigma parts
        for (unsigned int i = 1; i <= (double) n / 2; ++i) {
            x = a + (2 * i - 1) * coefficient;
            odd += function_1_arg(expression, x);
            // show process
            if (verbose) {
                printf("[#%d] f(xi[i = 2k-1]) = %lf, sigma(f(xi[i = 2k-1])) =  %lf\n",
                       2 * i - 1, function_1_arg(expression, x), odd);
            } // end of if verbose
        } // end of for loop

        // add even and odd sigma parts multiplied by their weights to area
        area += 2 * even + 4 * odd;
        // multiply to width/3 to get final area
        area *= coefficient / 3;
        if (verbose) {
            printf("\nArea = h/3 * [f(x0) + f(xn) + 2 * sigma(f(xi[i = 2k])) + 4 * sigma(f(xi[i = 2k-1]))]\n"
                   "Area = %lf/3 * [%lf + %lf + 2 * %lf + 4 * %lf]\n", coefficient, function_1_arg(expression, a),
                   function_1_arg(expression, b), even, odd);
        } // end of if verbose
    } else {
        // use simpson 3/8 rule, this method is based on cubic interpolation
        // sum both cubic and regular sigma parts
        for (unsigned int i = 1; i < n; ++i) {
            x = a + i * coefficient;
            if (i % 3 == 0) {
                cubic += function_1_arg(expression, x);
                // show process
                if (verbose) {
                    printf("[#%d] f(xi[i = 3k]) = %lf, sigma(f(xi[i = 3k])) =  %lf\n",
                           i, function_1_arg(expression, x), cubic);
                } // end of if verbose
            } else {
                regular += function_1_arg(expression, x);
                // show process
                if (verbose) {
                    printf("[#%d] f(xi[i != 3k]) = %lf, sigma(f(xi[i != 3k])) =  %lf\n",
                           i, function_1_arg(expression, x), regular);
                } // end of if verbose
            } // end of if else
        } // end of for loop

        // add cubic and regular sigma parts multiplied by their weights to area
        area += 3 * regular + 2 * cubic;
        // multiply to 3*width/8 to get final area
        area *= 3 * coefficient / 8;
        // show process
        if (verbose) {
            printf("\nArea = 3*h/8 * [f(x0) + f(xn) + 3 * sigma(f(xi[i != 3k])) + 2 * sigma(f(xi[i = 3k]))]\n"
                   "Area = 3*%lf/8 * [%lf + %lf + 3 * %lf + 2 * %lf]\n", coefficient, function_1_arg(expression, a),
                   function_1_arg(expression, b), regular, cubic);
        } // end of if verbose
    } // end of if else

    return area;
} // end of riemann sum function