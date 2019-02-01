#include "gradientDescentAlgorithm.h"
#include "../Util/randomGenerator.h"
#include "../Util/functions.h"
#include "../Util/_configurations.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                       int mode, int *state) {
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
     * mode         show process {0: no, 1: yes}
     * state        is answer found or not
     *
     */

    // check error thresholds
    if (ere < 0 || ete < 0) {
        printf("\nError: ete or ere or tol argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check mode
    if (mode != 0 && mode != 1) {
        printf("\nError: mode argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("Error: argument maxiter must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of maxiter check

    // initializing variables
    unsigned int iter = 0;
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

double gradientDescentInterval(const char *expression, double a, double b, double ete, double ere, double gamma,
                               unsigned int maxiter, int mode) {
    /*
     * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
     * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
     * the gradient (or approximate gradient) of the function at the current point.
     *
     * This function searches minimum on an interval [a, b]
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
     * ete          estimated true error
     * ere          estimated relative error
     * gamma        step size (also known as learning rate)
     * maxiter      maximum iteration threshold
     * mode         show process {0: no, 1: yes}
     *
     */

    // fix interval reverse
    if (a > b) {
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check error thresholds
    if (ere < 0 || ete < 0) {
        printf("\nError: ete or ere or tol argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check mode
    if (mode != 0 && mode != 1) {
        printf("\nError: mode argument is not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("Error: argument maxiter must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of maxiter check

    // initializing variables
    unsigned int iter = 0, innerIter = 0;
    // choose and arbitrary result at midpoint between a and b to be updated later
    double coefficient = (b - a), result = a + coefficient / 2;
    double x, past_x, fx, fresult;
    double ete_err, ere_err;
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // set the seed for random number generator
    seed();

    while (iter < maxiter) {
        // try maxiter times to find minimum in given interval [a, b] and return lowest result
        // update fresult with new result
        fresult = function_1_arg(expression, result);
        // choose a random starting point
        x = a + coefficient * zeroToOneUniformRandom();

        // set inner iter to zero before new loop
        innerIter = 0;
        // go in a loop to find a minimum with random starting point
        while (innerIter < maxiter) {
            // calculate new x by subtracting the derivative of function at x multiplied by gamma from x
            past_x = x;
            x -= firstDerivative_1_arg(expression, x, DX) * gamma;
            fx = function_1_arg(expression, x);

            // calculate errors
            ete_err = fabs(past_x - x);
            ere_err = fabs(ete_err / x);

            if (mode) {
                printf("\nIn this iteration [#%d][#%d], x = %.5e f(x) = %.5e\n"
                       "and estimated true error = %.5e and estimated relative error = %.5e,\n",
                       iter, innerIter, x, fx, ete_err, ere_err);
            } // end if(mode)

            // Termination Criterion
            // if new x goes beyond interval lower than a
            if (x < a) {
                if (mode) {
                    printf("\nIn this iteration the calculated x is less than a : %.5e < %f"
                           "so minimum of the function occurs at a\n",
                           x, a);
                } // end if(mode)

                // if fa is lower than f(result), then a is where the minimum occurs
                if (fa < fresult) {
                    result = a;
                } // end of if
                break;
            } // end of if

            // if new x goes beyond interval bigger than b
            if (x > b) {
                if (mode) {
                    printf("\nIn this iteration the calculated x is bigger than b : %.5e > %f"
                           "so minimum of the function occurs at b\n",
                           x, b);
                } // end if(mode)

                // if fb is lower than f(result), then b is where the minimum occurs
                if (fb < fresult) {
                    result = b;
                } // end of if
                break;
            } // end of if

            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("\nIn this iteration the calculated estimated true error is less than the threshold\n"
                           "(estimated true error) %.5e < %.5e (threshold)\n"
                           "so the calculated x is the point on domain that minimum of the function happens\n",
                           ete_err, ete);
                } // end if(mode)

                // if fx is lower than f(result), then x is where the minimum occurs
                if (fx < fresult) {
                    result = x;
                } // end of if
                break;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (mode) {
                    printf("\nIn this iteration the calculated estimated real error is less than the threshold\n"
                           "(estimated real error) %.5e < %.5e (threshold)\n"
                           "so the calculated x is the point on domain that minimum of the function happens\n",
                           ere_err, ere);
                } // end if(mode)

                // if fx is lower than f(result), then x is where the minimum occurs
                if (fx < fresult) {
                    result = x;
                } // end of if
                break;
            } // end of estimated relative error check
            innerIter++;
        }
        iter++;
    } // end of while loop

    // return result
    return result;
}