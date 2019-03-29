#include "brentAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double brent(const char *expression, double a, double b, double tol, unsigned int maxiter, int verbose, int *state) {

    // fix interval reverse
    if (a > b) {
        EZ_SWAP(a, b);
    } // end of if

    // check interval
    if (a == b) {
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check error threshold
    if (tol < 0) {
        printf("\nError: tol argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("\nError: argument maxiter must be more than zero!\n");
        Exit(EXIT_FAILURE);
    } // end of maxiter check

    // check verbose
    if (verbose != 0 && verbose != 1) {
        printf("\nError: verbose argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // set state to has a root at start of program
    // it would be changed if root couldn't be found
    *state = HAS_A_ROOT;

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // check interval edges
    if (fa == 0) {
        if (verbose) {
            printf("Root has been found at the start of interval [a, b].\n");
        } // end if(verbose)

        return a;
    } else if (fb == b) {
        if (verbose) {
            printf("Root has been found at the start of interval [a, b].\n");
        } // end if(verbose)

        return b;
    } else if (fa * fb < 0) {
        // if y1 and y2 have different signs, so we can use brent method
        // because when we bracket a function in two end of an interval (a, b)
        // if and only if f(a)f(b) < 0, function should have at least 1 root in that interval,
        // assume f(a) > 0, then f(b) must be smaller than zero to hold the equation f(a)f(b) < 0
        // it's clear that the curve of function should intersect x-axis at some point between [a, b]
        // in order to move from f(a) > 0 to f(b) < 0

        // if magnitude of f(a) is less than magnitude of f(b)
        // swap a with b and fa with fb
        if (fabs(fa) < fabs(fb)) {
            EZ_SWAP(a, b);
            EZ_SWAP(fa, fb);
        } // end of if

        // initializing variables
        unsigned int iter = 1, flag = 1;
        double s = 0, fs = 0, c = a, fc = fa, d = 0, error = tol;

        while (iter <= maxiter) {

            // Termination Criterion
            if (tol != 0 && error < tol) {
                if (verbose) {
                    printf("\nIn this iteration [#%d]: |b - a| < tolerance -> [%g < %g],\n"
                           "so x is close enough to the root of function.\n\n", iter - 1, error, tol);
                } // end if(verbose)

                return s;
            } // end of tolerance check

            if (fa != fc && fb != fc) {
                if (verbose) {
                    printf("In this iteration [%d]: using inverse quadratic interpolation.\n", iter);
                } // end if(verbose)

                // use inverse quadratic interpolation
                // I can explain it here but ... em ... why not searching it at wikipedia?
                s = (a * fb * fc / ((fa - fb) * (fa - fc))) +
                    (b * fa * fc / ((fb - fa) * (fb - fc))) +
                    (c * fa * fb / ((fc - fa) * (fc - fb)));
            } else {
                if (verbose) {
                    printf("In this iteration [%d]: using secant method.\n", iter);
                } // end if(verbose)

                // secant method
                // try wikipedia for more explanations
                s = b - fb * (b - a) / (fb - fa);
            } // end of if else

            // horror movie ahead, don't freak out!
            // it's just a condition testing
            // that is required by brent method
            if (((s < (3 * a + b) * 0.25) || (s > b)) ||
                (flag && fabs(s - b) >= fabs(b - c) * 0.5) ||
                (!flag && fabs(s - b) >= fabs(c - d) * 0.5) ||
                (flag && fabs(b - c) < tol) ||
                (!flag && fabs(c - d) < tol)) {

                if (verbose) {
                    printf("then using bisection method.\n");
                } // end if(verbose)

                // bisection method
                // wik ... ok ok you already knew what i'm going to say
                s = (a + b) * 0.5;

                // set flag
                flag = 1;
            } else {
                // clear flag
                flag = 0;
            } // end of if else

            // calculate fs
            fs = function_1_arg(expression, s);

            //substitute variables for next loop
            d = c;
            c = b;
            fc = fb;

            // interval reduction
            // in this part of brent's algorithm we are trying to reduce
            // interval for next iteration, we need to locate the root's
            // position between [a, s, b], by a simple test f(a)f(s) ?< 0
            // and then re-bracket the domain
            if (fa * fs < 0) {
                if (verbose) {
                    printf("Searching interval has been reduced, 'b' has been replaced by 's'.\n");
                } // end if(verbose)

                b = s;
                fb = fs;
            } else {
                if (verbose) {
                    printf("Searching interval has been reduced, 'a' has been replaced by 's'.\n");
                } // end if(verbose)

                a = s;
                fa = fs;
            } // end of if

            // calculate error
            error = fabs(b - a);

            if (verbose) {
                printf("\nNext iteration set is:\n"
                       "[(a, b), c, d, s, flag, error] = [(%g, %g), %g, %g, %g, %d, %g].\n\n",
                       a, b, c, d, s, flag, error);
            } // end if(verbose)

            iter++;
        } // end of while loop

        if (verbose) {
            // if user wanted to calculate root on maximum iteration limit
            // without specifying a tolerance error then the answer is what user wants
            if (tol == 0) {
                printf("\nWith maximum iteration of %d :\n", maxiter);
            } else {
                // if tolerance has been set and algorithm reached maximum iteration limit,
                // then the answer has not been found
                printf("\nThe solution does not converge or iterations are not sufficient.\n");
            } // end of if ... else

            printf("the last calculated root is x = %g .\n", s);
        } // end if(verbose)

        // error has been set but reaches to maxiter, means algorithms didn't converge to a root
        if (tol != 0) {
            // set state to 0 (false)
            *state = 0;
        } // end of if
        return s;

    } else { // if y1 and y2 have same signs, then we can't use bisection method
        if (verbose) {
            printf("Incorrect bracketing of function domain!\n"
                   "keep in mind that the inequality f(a) * f(b) < 0 must be correct\n"
                   "in order to use Brent's method.\n");
        }// end if(verbose)

        *state = HAS_NO_ROOT;
        return -1;
    } // end of if ... else
} // end of brent function
