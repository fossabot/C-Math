#include "secantAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double secant(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
              int verbose, int *state) {
    /*
     * In numerical analysis, the secant method is a root-finding algorithm that uses a succession of roots
     * of secant lines to better approximate a root of a function f. The secant method can be thought of as
     * a finite-difference approximation of Newton's method. However, the method was developed independently
     * of Newton's method and predates it by over 3000 years
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
     * ete          estimated true error
     * ere          estimated relative error
     * tol          tolerance error
     * maxiter      maximum iteration threshold
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, will set value of state to 0 if no answers been found
     *
     */

// fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check interval
    if (a == b) {
        printf("Error: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0){
        printf("\nError: ete or ere or tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("Error: argument maxiter must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of maxiter check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initializing variables
    unsigned int iter = 1;
    double c = 0;
    double fc, ete_err, ere_err;

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    while (iter <= maxiter) {
        // calculate c
        c = b - fb * (b - a) / (fb - fa);
        // evaluate the function at point c, y3 =f(c)
        fc = function_1_arg(expression, c);

        if (verbose) {
            printf("\nIteration number [#%d]: x%d = %lf, f(x%d) = %lf .\n", iter, iter, c, iter, fc);
        } // end of if verbose

        //calculate errors
        ete_err = fabs(c - b);
        ere_err = fabs((c - b) / b);

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (verbose) {
                printf("\nIn this iteration, |x%d - x%d| < estimated true error [%.5e < %.5e],\n"
                       "so x is close enough to the root of function.\n\n", iter, iter - 1, ete_err, ete);
            } // end if(verbose)

            return c;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (verbose) {
                printf("\nIn this iteration, |(x%d - x%d / x%d)| < estimated relative error [%.5e < %.5e],\n"
                       "so x is close enough to the root of function.\n\n", iter, iter - 1, iter, ere_err, ere);
            } // end if(verbose)

            return c;
        } // end of estimated relative error check

        // if y3 is less than tolerance error threshold
        if (tol != 0 && fabs(fc) < tol) {
            if (verbose) {
                printf("\nIn this iteration, |f(x%d)| < tolerance [%.5e < %.5e],\n"
                       "so x is close enough to the root of function.\n\n", iter, fabs(fc), tol);
            } // end if(verbose)

            return c;
        } // end of tolerance check

        // update variables for next iteration
        a = b;
        fa = fb;
        b = c;
        fb = fc;
        iter++;

    } // end of while loop

    // answer didn't found
    if (verbose) {
        if (ete == 0 && ere == 0 && tol == 0) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient.\n");
        } // end of if ... else

        printf("the last calculated x is %lf .\n", c);
    } // end if(verbose)

    // set state to 0 (false)
    *state = 0;
    return c;
} // end of secant function