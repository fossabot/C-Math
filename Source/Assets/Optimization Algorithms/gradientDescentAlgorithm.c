#include "gradientDescentAlgorithm.h"
#include "../Differentiation Algorithms/derivNumericalAlgorithm.h"
#include "../Util/randomGenerator.h"
#include "../Util/functions.h"
#include "../Util/_configurations.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                       int maximum, int verbose, int *state) {
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
     * maximum      this option will let user to find maximum instead of minimum {0: no, 1: yes}
     * verbose      show process {0: no, 1: yes}
     * state        is answer found or not
     *
     */

    // check error thresholds
    if (ere < 0 || ete < 0) {
        printf("\nError: ete or ere arguments are not valid.\n");
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
    unsigned int iter = 1;
    int modeCoefficient = (maximum == 0) ? 1 : -1;
    double fx, ete_err, ere_err, past_x;

    while (iter <= maxiter) {
        // calculate new x0 by subtracting the derivative of function at x0 multiplied by gamma from x0
        past_x = x0;
        x0 -= modeCoefficient * firstDerivative_1_arg(expression, x0, DX, CENTRAL_DIFFERENCE) * gamma;
        fx = function_1_arg(expression, x0);

        // calculate errors
        ete_err = fabs(past_x - x0);

        if (x0 != 0) {
            ere_err = fabs(ete_err / x0);
        } else {
            ere_err = ere;
        } // end of zero-division guard

        if (verbose) {
            printf("\nIn this iteration [#%d], x = %g f(x) = %g\n"
                   "and estimated true error = %g and estimated relative error = %g .\n",
                   iter, x0, fx, ete_err, ere_err);
        } // end if(verbose)

        // Termination Criterion
        // if calculated error is less than estimated true error threshold
        if (ete != 0 && ete_err < ete) {
            if (verbose) {
                printf("\nIn this iteration the calculated estimated true error is less than the threshold.\n"
                       "(estimated true error) %g < %g (threshold).\n", ete_err, ete);

                if (maximum) {
                    printf("so the calculated x is the point on domain that maximum of the function happens.\n");
                } else {
                    printf("so the calculated x is the point on domain that minimum of the function happens.\n");
                } // end of if
            } // end if(verbose)

            return x0;
        } // end of estimated true error check

        // if calculated error is less than estimated relative error threshold
        if (ere != 0 && ere_err < ere) {
            if (verbose) {
                printf("\nIn this iteration the calculated estimated real error is less than the threshold.\n"
                       "(estimated real error) %g < %g (threshold).\n", ere_err, ere);

                if (maximum) {
                    printf("so the calculated x is the point on domain that maximum of the function happens.\n");
                } else {
                    printf("so the calculated x is the point on domain that minimum of the function happens.\n");
                } // end of if
            } // end if(verbose)

            return x0;
        } // end of estimated relative error check

        iter++;
    } // end of while loop

    // answer didn't found
    if (verbose) {
        if (ete == 0 && ere == 0) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient.\n");
        } // end of if ... else
    } // end if(verbose)

    printf("the last calculated extremum is %g .\n", x0);
    // error has been set but reaches to maxiter, means algorithms didn't converge to an extremum
    if (ete != 0 && ere != 0) {
        // set state to 0 (false)
        *state = 0;
    }
    return x0;
} // end of gradientDescent function

double gradientDescentInterval(const char *expression, double a, double b, double ete, double ere, double gamma,
                               unsigned int maxiter, int maximum, int verbose) {
    /*
     * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
     * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
     * the gradient (or approximate gradient) of the function at the current point.
     *
     * This function searches minimum/maximum on an interval [a, b]
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * a            starting point of interval [a, b]
     * b            ending point of interval [a, b]
     * ete          estimated true error
     * ere          estimated relative error
     * gamma        step size (also known as learning rate)
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
    if (ere < 0 || ete < 0) {
        printf("\nError: ete or ere arguments are not valid.\n");
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
    unsigned int iter = 1, innerIter;
    int modeCoefficient = (maximum == 0) ? 1 : -1;
    // choose an arbitrary result at midpoint between a and b to be updated later
    double coefficient = (b - a), result = a + coefficient / 2;
    double x, past_x, static_x, fx, fresult;
    double ete_err, ere_err;
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // set the seed for random number generator
    seed();

    while (iter <= maxiter) {
        // try maxiter times to find minimum in given interval [a, b] and return lowest result
        // update fresult with new result
        fresult = function_1_arg(expression, result);

        // Termination based on domain range
        if (coefficient < DX) {
            break;
        }

        // choose a random starting point
        x = a + coefficient * zeroToOneUniformRandom();

        // reset inner iter to zero before new loop
        innerIter = 1;
        // go in a loop to find a minimum with random starting point
        while (innerIter <= maxiter) {
            // calculate new x by subtracting the derivative of function at x multiplied by gamma from x
            static_x = x;
            past_x = x;
            x -= modeCoefficient * firstDerivative_1_arg(expression, x, DX, CENTRAL_DIFFERENCE) * gamma;
            fx = function_1_arg(expression, x);

            // if fx is lower than f(result), then x is where the minimum occurs
            if (!maximum && fx < fresult) {
                result = x;
            } // end of if

            // if fx is bigger than f(result), then x is where the maximum occurs
            if (maximum && fx > fresult) {
                result = x;
            } // end of if

            // calculate errors
            ete_err = fabs(past_x - x);

            if (x != 0) {
                ere_err = fabs(ete_err / x);
            } else {
                ere_err = ere;
            } // end of zero-division guard

            if (verbose) {
                printf("\nIn this iteration [#%d][#%d], x = %g f(x) = %g\n"
                       "and estimated true error = %g and estimated relative error = %g .\n",
                       iter, innerIter, x, fx, ete_err, ere_err);
            } // end if(verbose)

            // Termination Criterion
            // if new x goes beyond interval, lower than a
            if (!maximum && x < a) {
                if (verbose) {
                    printf("\nIn this iteration the calculated x is less than a : %g < %g "
                           "so minimum of the function occurs at a.\n",
                           x, a);
                } // end if(verbose)

                // if fa is lower than f(result), then a is where the minimum occurs
                if (fa < fresult) {
                    result = a;
                } // end of if

                // rearrange search domain
                a = static_x;
                coefficient = (b - a);
                break;
            } // end of if

            if (maximum && x < a) {
                if (verbose) {
                    printf("\nIn this iteration the calculated x is less than a : %g < %g "
                           "so maximum of the function occurs at a.\n",
                           x, a);
                } // end if(verbose)

                // if fa is lower than f(result), then a is where the minimum occurs
                if (fa > fresult) {
                    result = a;
                } // end of if

                // rearrange search domain
                a = static_x;
                coefficient = (b - a);
                break;
            } // end of if

            // if new x goes beyond interval, bigger than b
            if (!maximum && x > b) {
                if (verbose) {
                    printf("\nIn this iteration the calculated x is bigger than b : %g > %g "
                           "so minimum of the function occurs at b.\n",
                           x, b);
                } // end if(verbose)

                // if fb is lower than f(result), then b is where the minimum occurs
                if (fb < fresult) {
                    result = b;
                } // end of if

                // rearrange search domain
                b = static_x;
                coefficient = (b - a);
                break;
            } // end of if

            if (maximum && x > b) {
                if (verbose) {
                    printf("\nIn this iteration the calculated x is bigger than b : %g > %g "
                           "so maximum of the function occurs at b.\n",
                           x, b);
                } // end if(verbose)

                // if fb is bigger than f(result), then b is where the maximum occurs
                if (fb > fresult) {
                    result = b;
                } // end of if

                // rearrange search domain
                b = static_x;
                coefficient = (b - a);
                break;
            } // end of if

            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (verbose) {
                    printf("\nIn this iteration the calculated estimated true error is less than the threshold.\n"
                           "(estimated true error) %g < %g (threshold).\n", ete_err, ete);

                    if (maximum) {
                        printf("so the calculated x is the point on domain that maximum of the function happens.\n");
                    } else {
                        printf("so the calculated x is the point on domain that minimum of the function happens.\n");
                    } // end of if
                } // end if(verbose)

                break;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (verbose) {
                    printf("\nIn this iteration the calculated estimated real error is less than the threshold.\n"
                           "(estimated real error) %g < %g (threshold).\n", ere_err, ere);
                } // end if(verbose)

                if (maximum) {
                    printf("so the calculated x is the point on domain that maximum of the function happens.\n");
                } else {
                    printf("so the calculated x is the point on domain that minimum of the function happens.\n");
                } // end of if

                break;
            } // end of estimated relative error check

            innerIter++;
        } // end of inner while loop
        iter++;
    } // end of while loop

    // return result
    return result;
}