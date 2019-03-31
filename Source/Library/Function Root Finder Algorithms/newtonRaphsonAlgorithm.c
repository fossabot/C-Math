#include "newtonRaphsonAlgorithm.h"
#include "../Differentiation Algorithms/derivNumericalAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newtonRaphson(const char *expression, double x, double ete, double ere, double tol, unsigned int maxiter,
                     int verbose, int *state) {
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

    // calculates y = f(x) at initial point
    double fx = function_1_arg(expression, x);

    // first guess check
    if (fabs(fx) <= tol) {
        if (verbose) {
            printf("Root has been found at the initial point x.\n");
        } // end if(verbose)

        return x;
    }

    // initializing variables
    unsigned int iter = 1, dfx_counter = 2;
    double x_new, fx_new, dfx;
    double ete_err = ete, ere_err = ere, tol_err = tol;


    while (iter <= maxiter) {

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |x%d - x%d| < estimated true error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, ete_err,
                       ete);
            } // end if(verbose)

            return x;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |(x%d - x%d / x%d)| < estimated relative error [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, iter - 2, iter - 1,
                       ere_err, ere);
            } // end if(verbose)

            return x;
        } // end of estimated relative error check

        // if y3 is less than tolerance error threshold
        if (tol != 0 && tol_err < tol) {
            if (verbose) {
                printf("\nIn this iteration[#%d]: |f(x%d)| < tolerance [%g < %g],\n"
                       "so x is close enough to the root of function.\n\n", iter - 1, iter - 1, tol_err, tol);
            } // end if(verbose)

            return x;
        } // end of tolerance check

        // calculate derivative of function in the given point
        dfx = firstDerivative_1_arg(expression, x, DX, CENTRAL_DIFFERENCE);

        DFX_LABEL: // LABEL for go to
        // if derivative isn't equal to zero
        if (dfx) {

            // calculate new x by subtracting the derivative from x
            x_new = x - fx / dfx;

            // calculate new y at new root estimate x
            fx_new = function_1_arg(expression, x_new);

            if (verbose) {
                printf("Iteration number [#%d]: f(x%d) = %g, f'(x%d) = %g, delta(x%d) = f(x%d) / f'(x%d) = %g\n"
                       "x%d = x%d - delta(x%d) = %g , f(x%d) = %g.\n\n", iter, iter - 1, fx, iter - 1, dfx, iter - 1,
                       iter - 1, iter - 1, fx / dfx, iter, iter - 1, iter - 1, x_new, iter, fx_new);
            } // end of if verbose

            // calculate errors
            ete_err = fabs(fx / dfx);

            if (x != 0) {
                ere_err = fabs(ete_err / x);
            } else {
                ere_err = ere;
            } // end of zero-division guard

            tol_err = fabs(fx_new);

            // substitute variables for next iteration
            x = x_new;
            fx = fx_new;
            iter++;

        } else { // if derivative is equal to zero

            if (verbose) {
                if (dfx_counter == 2) {
                    printf("f'(x) = 0, trying another differentiation algorithm\n");
                } else if (dfx_counter > 8) {
                    printf("f'(x) = 0, this algorithm cannot find a root.\n");
                } else {
                    printf("using central derivation algorithm with %d order accuracy, still failed.", dfx_counter - 2);
                } // end of if
            } // end if(verbose)

            // try to get more precise derivative [up to eight order accuracy]
            if (dfx_counter <= 8) {

                // calculate new f'(x)
                dfx = centralFirstDerivative_1_arg(expression, x, DX, dfx_counter);
                dfx_counter += 2;

                // go back and check value
                goto DFX_LABEL;
            } else {
                if (verbose) {
                    printf("Newton-Raphson method can't solve f(x) = 0 if f'(x0) = 0 !\n"
                           "check your function and if you think it has derivative\n"
                           "then try to choose a better starting point x0 .\n");
                } // end if(verbose)
                // go out of while loop
                break;
            } // end of if else
        } // end of if(dfx)
    } // end of while loop

    if (verbose) {
        if (ete == 0 && ere == 0 && tol == 0 && iter > maxiter) {
            printf("\nWith maximum iteration of %d :\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient.\n");
        } // end of if ... else

        printf("the last calculated root is x = %g .\n", x);
    } // end if(verbose)

    // error has been set but reaches to maxiter, means algorithms didn't converge to a root
    if (!(ete == 0 && ere == 0 && tol == 0) || (ete == 0 && ere == 0 && tol && iter > maxiter)) {
        // set state to 0 (false)
        *state = HAS_NO_ROOT;
    } // end of if

    return x;
} // end of newton Raphson function