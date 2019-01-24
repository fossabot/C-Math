#include "bisectionAlgorithm.h"
#include "../Util/functions.h"

#include <stdio.h>
#include <math.h>

double bisection(const char *expression, double a, double b, double ete, double ere, double tol, int maxiter, int mode,
                 int *state) {
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
     * mode         show process
     * state        is answer found or not
     *
     */

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // if y1 and y2 have different signs, then we can use bisection method
    if (fa * fb < 0) {

        // initializing variables
        int iter = 1;
        double c = 0;
        double ete_err;
        double ere_err;

        while (iter <= maxiter) {
            // find the average of a and b
            c = (a + b) / 2;
            // evaluate the function at point c, y3 =f(c)
            double fc = function_1_arg(expression, c);

            if (mode) {
                printf("\nIteration number: [#%d]: c = %10.7lf, f(c) = %.10e  .\n", iter, c, fc);
            } // end if(mode)

            // if y3 and y1 have same signs, then substitute a by c and y1 by y3
            if (fc * fa > 0) {

                //calculate true error
                ete_err = fabs(a - c);

                // substitute
                a = c;
                fa = fc;

                if (mode) {
                    printf("In this iteration, a replaced by c, new range is [%lf, %lf].\n", a, b);
                } // end if(mode)

            } else if (fc * fb > 0) { // if y3 and y2 have same signs, then substitute b by c and y2 by y3

                //calculate true error
                ete_err = fabs(b - c);

                // substitute
                b = c;
                fb = fc;

                if (mode) {
                    printf("In this iteration, b replaced by c, new range is [%lf, %lf].\n", a, b);
                } // end if(mode)

            } else {
                if (mode) {
                    printf("In this iteration, f(c) = 0, so c is the root of function\n\n");
                } // end if(mode)

                return c;
            } // end of if .. else if chained decisions

            //calculate relative error
            ere_err = fabs(ete_err / c);

            // Termination Criterion
            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("\nIn this iteration, |c%d - c%d| < estimated true error [%.5e < %.5e],\n"
                           "so c is close enough to the root of function\n\n", iter, iter - 1, ete_err, ete);
                } // end if(mode)

                return c;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (mode) {
                    printf("\nIn this iteration, |(c%d - c%d / c%d)| < estimated relative error [%.5e < %.5e"
                           "],\nso c is close enough to the root of function\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(mode)

                return c;
            } // end of estimated relative error check

            // if y3 is less than tolerance error threshold
            if (tol != 0 && fabs(fc) < tol) {
                if (mode) {
                    printf("\nIn this iteration, |f(c)| < tolerance [%.5e < %.5e],\n"
                           "so c is close enough to the root of function\n\n", fabs(fc), tol);
                } // end if(mode)

                return c;
            } // end of tolerance check

            iter++;
        } // end of while loop

        // answer didn't found
        if (mode) {
            if (ete == 0 && ere == 0 && tol == 0) {
                printf("\nWith maximum iteration of %d\n", maxiter);
            } else {
                printf("\nThe solution does not converge or iterations are not sufficient\n");
            } // end of if ... else

            printf("the last calculated c is %lf\n", c);
        } // end if(mode)

        // set state to 0 (false)
        *state = 0;
        return c;

    } else { // if y1 and y2 have same signs, then we can't use bisection method
        if (mode) {
            printf("Incorrect bracketing of function domain!\n"
                   "keep in mind that the inequality f(a) * f(b) < 0 must be correct\n"
                   "in order to use Bisection method\n");
        }// end if(mode)

        *state = 0;
        return -1;
    } // end of if ... else
} // end of bisection function