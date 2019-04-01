#include "goldenSectionOptAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/configurations/asl_configurations.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double goldenSectionOptimization(const char *expression, double a, double b, double tol, unsigned int maxiter,
                                 int maximum, int verbose) {
    /*
     * The golden-section search is a technique for finding the extremum (minimum or maximum) of a strictly unimodal
     * function by successively narrowing the range of values inside which the extremum is known to exist.
     * The technique derives its name from the fact that the algorithm maintains the function values for triples of
     * points whose distances form a golden ratio. The algorithm is the limit of Fibonacci search (also described
     * below) for a large number of function evaluations. Fibonacci search and golden-section search were discovered
     * by Kiefer (1953) (see also Avriel and Wilde (1966)).
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
     * tol          error threshold
     * maxiter      maximum iteration threshold
     * maximum      this option will let user to find maximum instead of minimum {0: no, 1: yes}
     * verbose      show process {0: no, 1: yes}
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

    // check error thresholds
    if (tol < 0) {
        printf("\nError: tol arguments must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter < 0) {
        printf("\nError: argument maxiter must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of maxiter check

    // check maximum to be either 0 or 1
    if (maximum != 0 && maximum != 1) {
        printf("\nError: argument maximum must be either 0 or 1!\n");
        Exit(EXIT_FAILURE);
    } // end of maximum check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initializing variables
    unsigned int iter = 1, state;
    double range, x1, x2, fx1, fx2, fa, fb, ftest, error = (b - a);
    double xOptimal = 0;

    // calculate values
    range = ASL_PHI * (b - a);
    x1 = b - range;
    x2 = a + range;

    // evaluate function at points a and b
    fa = function_1_arg(expression, a);
    fb = function_1_arg(expression, b);
    // evaluate function at points x1 and x2
    fx1 = function_1_arg(expression, x1);
    fx2 = function_1_arg(expression, x2);

    if (verbose) {
        printf("Starting points : [a, x1, x2, b, range] = [%g, %g, %g, %g, %g] .\n", a, x1, x2, b, range);
    } // end if(verbose)

    while (iter <= maxiter) {

        if (xOptimal != 0 && iter != 1) {
            error = (1 - ASL_PHI) * fabs((b - a) / xOptimal);
        } // end of zero-division guard

        if (error < tol) {
            break;
        } // end of if


        // edge case analysis
        if (maximum) {
            // find bigger edge value
            if (fa >= fb) {
                ftest = fa;
                state = 0;
            } else {
                ftest = fb;
                state = 1;
            } // end of if


            if (ftest >= fx1 && ftest >= fx2) {
                if (state) {

                    xOptimal = b;
                    // substitute variables
                    a = x1;
                    x1 = x2;
                    fx1 = fx2;
                    // re-evaluate
                    range = ASL_PHI * (b - a);
                    x2 = a + range;
                    fx2 = function_1_arg(expression, x2);
                    fa = function_1_arg(expression, a);
                } else {

                    xOptimal = a;
                    // substitute variables
                    b = x2;
                    x2 = x1;
                    fx2 = fx1;
                    // re-evaluate
                    range = ASL_PHI * (b - a);
                    x1 = b - range;
                    fx1 = function_1_arg(expression, x1);
                    fb = function_1_arg(expression, b);
                } // end of if(state)

                // skip this cycle
                if (verbose) {
                    printf("\nIn this iteration [#%d]: edge case has happened.\n", iter);
                    printf("updated points : [a, x1, x2, b, range] = [%g, %g, %g, %g, %g] .\n", a, x1, x2, b, range);
                } // end if(verbose)
                iter++;
                continue;

            } // end of if(ftest >= fx1 && ftest >= fx2)
        } else {

            // find smaller edge value
            if (fa <= fb) {
                ftest = fa;
                state = 0;
            } else {
                ftest = fb;
                state = 1;
            } // end of if

            // compare edge value to inner values
            if (ftest <= fx1 && ftest <= fx2) {
                if (state) {

                    xOptimal = b;
                    // substitute variables
                    a = x1;
                    x1 = x2;
                    fx1 = fx2;
                    // re-evaluate
                    range = ASL_PHI * (b - a);
                    x2 = a + range;
                    fx2 = function_1_arg(expression, x2);
                    fa = function_1_arg(expression, a);
                } else {

                    xOptimal = a;
                    // substitute variables
                    b = x2;
                    x2 = x1;
                    fx2 = fx1;
                    // re-evaluate
                    range = ASL_PHI * (b - a);
                    x1 = b - range;
                    fx1 = function_1_arg(expression, x1);
                    fb = function_1_arg(expression, b);
                } // end of if(state)

                if (verbose) {
                    printf("\nIn this iteration [#%d]: edge case has happened.\n", iter);
                    printf("updated points : [a, x1, x2, b, range] = [%g, %g, %g, %g, %g] .\n", a, x1, x2, b, range);
                } // end if(verbose)
                // skip this cycle
                iter++;
                continue;

            } // end of if(ftest >= fx1 && ftest >= fx2)
        } // end of if else (edge case analysis)

        if (fx1 > fx2) {
            if (verbose) {
                printf("\nIn this iteration [#%d]: fx1 > fx2  -> %g > %g .\n", iter, fx1, fx2);
            } // end if(verbose)

            if (maximum) {

                xOptimal = x1;
                // substitute variables
                b = x2;
                x2 = x1;
                fx2 = fx1;
                // re-evaluate
                range = ASL_PHI * (b - a);
                x1 = b - range;
                fx1 = function_1_arg(expression, x1);
            } else {

                xOptimal = x2;
                // substitute variables
                a = x1;
                x1 = x2;
                fx1 = fx2;
                // re-evaluate
                range = ASL_PHI * (b - a);
                x2 = a + range;
                fx2 = function_1_arg(expression, x2);

            } // end of if else
        } else {
            if (verbose) {
                printf("\nIn this iteration [#%d]: fx1 < fx2  -> %g < %g .\n", iter, fx1, fx2);
            } // end if(verbose)

            if (maximum) {

                xOptimal = x2;
                // substitute variables
                a = x1;
                x1 = x2;
                fx1 = fx2;
                // re-evaluate
                range = ASL_PHI * (b - a);
                x2 = a + range;
                fx2 = function_1_arg(expression, x2);
            } else {

                xOptimal = x1;
                // substitute variables
                b = x2;
                x2 = x1;
                fx2 = fx1;
                // re-evaluate
                range = ASL_PHI * (b - a);
                x1 = b - range;
                fx1 = function_1_arg(expression, x1);

            } // end of if else
        } // end of if else

        if (verbose) {
            printf("updated points : [a, x1, x2, b, range] = [%g, %g, %g, %g, %g] .\n", a, x1, x2, b, range);
        } // end if(verbose)

        iter++;
    } // end of while loop

    if (verbose) {
        if (tol && iter <= maxiter) {
            printf("\nIn this iteration [#%d]: error < tolerance -> %g < %g \n", iter - 1, error, tol);
        } else {
            printf("\nWith maximum iteration of %d \n", maxiter);
        }

        printf("the last calculated extremum point is x = %g .\n", xOptimal);
    } // end if(verbose)

    return xOptimal;
} // end of goldenSectionOptimization function