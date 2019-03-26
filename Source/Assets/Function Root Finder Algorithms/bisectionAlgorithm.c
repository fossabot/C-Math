#include "bisectionAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double bisection(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
                 int verbose, int *state) {
    /*
     * The Bisection method in mathematics is a root-finding method that repeatedly bisects an interval and then selects
     * a sub-interval in which a root must lie for further processing. It is a very simple and robust method, but it is
     * also relatively slow. Because of this, it is often used to obtain a rough approximation to a solution which is
     * then used as a starting point for more rapidly converging methods. The method is also called the interval
     * halving method, the binary search method, or the dichotomy method.
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
        printf("\nError: improper interval!\n");
        Exit(EXIT_FAILURE);
    } //end of interval check

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0){
        printf("\nError: ete or ere or tol argument is not valid.\n");
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

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // if y1 and y2 have different signs, then we can use bisection method
    if (fa * fb < 0) {

        // initializing variables
        unsigned int iter = 1;
        double x = 0;
        double ete_err;
        double ere_err;

        while (iter <= maxiter) {
            // find the average of a and b
            x = (a + b) / 2;
            // evaluate the function at point x, y3 =f(x)
            double fc = function_1_arg(expression, x);

            if (verbose) {
                printf("\nIteration number [#%d]: x = %10.7lf, f(x) = %.10e .\n", iter, x, fc);
            } // end if(verbose)

            // if y3 and y1 have same signs, then substitute a by x and y1 by y3
            if (fc * fa > 0) {

                //calculate true error
                ete_err = fabs(a - x);

                // substitute
                a = x;
                fa = fc;

                if (verbose) {
                    printf("In this iteration, a replaced by x, new range is [%g, %g].\n", a, b);
                } // end if(verbose)

            } else if (fc * fb > 0) { // if y3 and y2 have same signs, then substitute b by x and y2 by y3

                //calculate true error
                ete_err = fabs(b - x);

                // substitute
                b = x;
                fb = fc;

                if (verbose) {
                    printf("In this iteration, b replaced by x, new range is [%g, %g].\n", a, b);
                } // end if(verbose)

            } else {
                if (verbose) {
                    printf("In this iteration, f(x) = 0, so x is the root of function.\n\n");
                } // end if(verbose)

                return x;
            } // end of if .. else if chained decisions

            //calculate relative error
            if (x != 0) {
                ere_err = fabs(ete_err / x);
            } else {
                ere_err = ere;
            } // end of zero-division guard

            // Termination Criterion
            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (verbose) {
                    printf("\nIn this iteration, |x%d - x%d| < estimated true error [%g < %g],\n"
                           "so x is close enough to the root of function.\n\n", iter, iter - 1, ete_err, ete);
                } // end if(verbose)

                return x;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (verbose) {
                    printf("\nIn this iteration, |(x%d - x%d / x%d)| < estimated relative error [%g < %g"
                           "],\nso x is close enough to the root of function.\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(verbose)

                return x;
            } // end of estimated relative error check

            // if y3 is less than tolerance error threshold
            if (tol != 0 && fabs(fc) < tol) {
                if (verbose) {
                    printf("\nIn this iteration, |f(x)| < tolerance [%g < %g],\n"
                           "so x is close enough to the root of function.\n\n", fabs(fc), tol);
                } // end if(verbose)

                return x;
            } // end of tolerance check

            iter++;
        } // end of while loop

        // answer didn't found
        if (verbose) {
            if (ete == 0 && ere == 0 && tol == 0) {
                printf("\nWith maximum iteration of %d\n", maxiter);
            } else {
                printf("\nThe solution does not converge or iterations are not sufficient.\n");
            } // end of if ... else

            printf("the last calculated x is %g .\n", x);
        } // end if(verbose)

        // error has been set but reaches to maxiter, means algorithms didn't converge to a root
        if (ete != 0 && ere != 0 && tol != 0) {
            // set state to 0 (false)
            *state = 0;
        }
        return x;

    } else { // if y1 and y2 have same signs, then we can't use bisection method
        if (verbose) {
            printf("Incorrect bracketing of function domain!\n"
                   "keep in mind that the inequality f(a) * f(b) < 0 must be correct\n"
                   "in order to use Bisection method.\n");
        }// end if(verbose)

        *state = 0;
        return -1;
    } // end of if ... else
} // end of bisection function