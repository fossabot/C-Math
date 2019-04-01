#include "newtonRaphsonOptAlgorithm.h"
#include "../Differentiation Algorithms/derivNumericalAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newtonRaphsonOptimization(const char *expression, double x0, double ete, double ere, double tol,
                                 unsigned int maxiter, int verbose, int *state) {
    /*
     * In numerical analysis, Newton's method (also known as the Newton–Raphson method), named after Isaac Newton and
     * Joseph Raphson, is a method for finding successively better approximations to the roots (or zeroes) of
     * a real-valued function.
     * The Newton–Raphson method in one variable is implemented as follows:
     * The method starts with a function f defined over the real numbers x, the function's derivative f ′, and an initial
     * guess x0 for a root of the function f. If the function satisfies the assumptions made in the derivation of
     * the formula and the initial guess is close, then a better approximation x1 is:
     *
     * x1 = x0 - f(x0)/f'(x0)
     *
     * Geometrically, (x1, 0) is the intersection of the x-axis and the tangent of the graph of f at (x0, f (x0)).
     * The process is repeated until a sufficiently accurate value is reached.
     *
     * to find extremum of a function using Newton's method we should find the root of it's first derivative
     * by calculating f' = 0 we will reach to approximation:
     *
     * x1 = x0 - f'(x0)/f''(x0)
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x0           starting point
     * ete          estimated true error
     * ere          estimated relative error
     * tol          tolerance error
     * maxiter      maximum iteration threshold
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not, will set value of state to 0 if no answers been found
     *
     */

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0) {
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

    // initializing variables
    double x = x0;
    double xNew, dfxNew, d2fx;
    double ete_err, ere_err;
    double dfx = centralFirstDerivative_1_arg(expression, x, ASL_EPSILON, ASL_EIGHTH_ORDER_ACCURACY);
    unsigned int iter = 1;

    while (iter <= maxiter) {
        // calculate derivative of function in the given point
        d2fx = centralSecondDerivative_1_arg(expression, x, ASL_EPSILON, ASL_EIGHTH_ORDER_ACCURACY);

        // if derivative isn't equal to zero
        if (d2fx) {
            // calculate new x by subtracting the derivative from x
            xNew = x - dfx / d2fx;
            dfxNew = centralFirstDerivative_1_arg(expression, xNew, ASL_EPSILON, ASL_EIGHTH_ORDER_ACCURACY);

            if (verbose) {
                printf("\nIteration number [#%d]: f'(x%d) = %g, f''(x%d) = %g, delta(x%d) = f'(x%d) / f''(x%d) = %g\n"
                       "\t\t\tx%d = x%d - delta(x%d) = %g.\n", iter, iter - 1, dfx, iter - 1, d2fx, iter - 1,
                       iter - 1, iter - 1, dfx / d2fx, iter, iter - 1, iter - 1, xNew);
            } // end of if verbose

            // calculate errors
            ete_err = fabs(dfx / d2fx);

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
                           "so x is close enough to the extremum of function.\n\n", iter, iter - 1, ete_err, ete);
                } // end if(verbose)

                return x;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (verbose) {
                    printf("\nIn this iteration, |(x%d - x%d / x%d)| < estimated relative error [%g < %g],\n"
                           "so x is close enough to the extremum of function.\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(verbose)

                return x;
            } // end of estimated relative error check

            // if fx is less than tolerance error threshold
            if (tol != 0 && fabs(dfx) < tol) {
                if (verbose) {
                    printf("\nIn this iteration, |f(x%d)| < tolerance [%g < %g],\n"
                           "so x is close enough to the extremum of function.\n\n", iter, fabs(dfx), tol);
                } // end if(verbose)

                return x;
            } // end of tolerance check

            x = xNew;
            dfx = dfxNew;
            iter++;

        } else { // if derivative is  equal to zero
            if (verbose) {
                printf("Newton-Raphson method can't solve f'(x) = 0 if f''(x0) = 0 !\n"
                       "check your function and if you think it has derivative\n"
                       "then try to choose a better starting point x0 .\n");
            } // end of if
            // go out of while loop
            break;
        } // end of if(dfx)
    } // end of while loop

    // answer didn't found
    if (verbose) {
        if (ete == 0 && ere == 0 && tol == 0 && iter > maxiter) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient.\n");
        } // end of if ... else

        printf("the last calculated x is %g .\n", x);
    } // end if(verbose)

    // error has been set but reaches to maxiter, means algorithms didn't converge to an extremum
    if (ete != 0 && ere != 0 && tol != 0 && iter <= maxiter) {
        // set state to 0 (false)
        *state = 0;
    } // end of if

    return x;
} // end of newtonRaphsonOptimization function