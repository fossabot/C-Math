#include "newtonRaphsonAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"
#include "../Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double newtonRaphson(const char *expression, double x0, double ete, double ere, double tol, unsigned int maxiter,
                     int mode, int *state) {
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
     * mode         show process {0: no, 1: yes}
     * state        is answer found or not
     *
     */

    // check mode
    if (mode != 0 && mode != 1){
        printf("\nError: mode argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    }

    // initializing variables
    unsigned int iter = 1;
    double x = x0;
    double xNew;
    double fx = function_1_arg(expression, x);
    double fxNew;
    double dfx;
    double ete_err;
    double ere_err;

    while (iter <= maxiter) {
        // calculate derivative of function in the given point
        dfx = firstDerivative_1_arg(expression, x, DX);

        // if derivative isn't equal to zero
        if (dfx) {
            // calculate new x by subtracting the derivative from x
            xNew = x - fx / dfx;
            fxNew = function_1_arg(expression, xNew);

            if (mode) {
                printf("\nIteration number [#%d]: f(x%d) = %lf, f'(x%d) = %lf, delta(x%d) = f(x%d) / f'(x%d) = %lf\n"
                       "\t\t\tx%d = x%d - delta(x%d) = %.10e\n", iter, iter - 1, fx, iter - 1, dfx, iter - 1, iter - 1,
                       iter - 1, fx / dfx, iter, iter - 1, iter - 1, xNew);
            } // end of if mode

            // calculate errors
            ete_err = fabs(fx / dfx);
            ere_err = fabs(ete_err / x);

            // Termination Criterion
            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("\nIn this iteration, |x%d - x%d| < estimated true error [%.5e < %.5e],\n"
                           "so x is close enough to the root of function\n\n", iter, iter - 1, ete_err, ete);
                } // end if(mode)

                return x;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (mode) {
                    printf("\nIn this iteration, |(x%d - x%d / x%d)| < estimated relative error [%.5e < %.5e],\n"
                           "so x is close enough to the root of function\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(mode)

                return x;
            } // end of estimated relative error check

            // if fx is less than tolerance error threshold
            if (tol != 0 && fabs(fx) < tol) {
                if (mode) {
                    printf("\nIn this iteration, |f(x%d)| < tolerance [%.5e < %.5e],\n"
                           "so x is close enough to the root of function\n\n", iter, fabs(fx), tol);
                } // end if(mode)

                return x;
            } // end of tolerance check

            x = xNew;
            fx = fxNew;
            iter++;

        } else { // if derivative is  equal to zero
            if (mode) {
                printf("Newton-Raphson method can't solve f(x) = 0 if f'(x0) = 0 !\n"
                       "check your function and if you think it has derivative then try to choose a better x0\n");
            }

            // set state to 0 (false)
            *state = 0;
            return -1;
        } // end of if(dfx)

    } // end of while loop

    // answer didn't found
    if (mode) {
        if (ete == 0 && ere == 0 && tol == 0) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient\n");
        } // end of if ... else

        printf("the last calculated x is %lf\n", x);
    } // end if(mode)

    // set state to 0 (false)
    *state = 0;
    return -1;
} // end of newton Raphson function