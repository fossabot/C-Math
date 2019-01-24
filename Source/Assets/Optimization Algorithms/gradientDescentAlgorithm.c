#include "gradientDescentAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/_configurations.h"

#include <stdio.h>
#include <math.h>

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, int maxiter, int mode,
                       int *state) {
    /*
     * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
     * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
     * the gradient (or approximate gradient) of the function at the current point.
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x0           starting point
     * ete          estimated true error
     * ere          estimated relative error
     * gamma        step size (also known as learning rate)
     * maxiter      maximum iteration threshold
     * mode         show process
     * state        is answer found or not
     *
     */

    // initializing variables
    int iter = 0;
    double fx;
    double ete_err;
    double ere_err;
    double past_x;

    while (iter < maxiter) {
        // calculate new x0 by subtracting the derivative of function at x0 multiplied by gamma from x0
        past_x = x0;
        x0 -= firstDerivative_1_arg(expression, x0, DX) * gamma;
        fx = function_1_arg(expression, x0);

        // calculate errors
        ete_err = fabs(past_x - x0);
        ere_err = fabs(ete_err / x0);

        if (mode) {
            printf("\nIn this iteration [#%d], x = %.5e f(x) = %.5e\n"
                   "and estimated true error = %.5e and estimated relative error = %.5e,\n",
                   iter, x0, fx, ete_err, ere_err);
        } // end if(mode)

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (mode) {
                printf("\nIn this iteration the calculated estimated true error is less than the threshold\n"
                       "(estimated true error) %.5e < %.5e (threshold)\n"
                       "so the calculated x is the point on domain that minimum of the function happens\n",
                       ete_err, ete);
            } // end if(mode)

            return x0;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (mode) {
                printf("\nIn this iteration the calculated estimated real error is less than the threshold\n"
                       "(estimated real error) %.5e < %.5e (threshold)\n"
                       "so the calculated x is the point on domain that minimum of the function happens\n",
                       ere_err, ere);
            } // end if(mode)

            return x0;
        } // end of estimated relative error check

        iter++;
    } // end of while loop

    // answer didn't found
    if (mode) {
        if (ete == 0 && ere == 0) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient\n");
        } // end of if ... else

        printf("the last calculated x is %lf\n", x0);
    } // end if(mode)

    // set state to 0 (false)
    *state = 0;
    return x0;
} // end of gradientDescent function