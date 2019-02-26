#include "falsePositionAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double
falsePosition(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
              int options, int mode, int *state) {
    /*
     * In mathematics, the false position method or regula falsi is a very old method for solving
	 * an equation in one unknown, that, in modified form, is still in use. In simple terms, 
	 * the method is the trial and error technique of using test ("false") values for the variable 
	 * and then adjusting the test value according to the outcome. This is sometimes also referred
	 * to as "guess and check". Versions of the method predate the advent of algebra and the use of equations.
     *
     * ARGUMENTS:
     * expressions   the function expression, it must be a string array like "x^2+1"
     * a             starting point of interval [a, b]
     * b             ending point of interval [a, b]
     * ete           estimated true error
     * ere           estimated relative error
     * tol           tolerance error
     * maxiter       maximum iteration threshold
     * options       use improvement algorithms  {0: no, 1: illinois, 2: anderson-bjork}
     * mode          show process {0: no, 1: yes}
     * state         is answer found or not, will set value of state to 0 if no answers been found
     *
     */

    // fix interval reverse
    if (a > b){
        double temp = a;
        a = b;
        b = temp;
    } // end of if

    // check error thresholds
    if (ere < 0 || ete < 0 || tol < 0){
        printf("\nError: ete or ere or tol argument is not valid.\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check mode and options value
    if ((mode != 0 && mode != 1) || (options != 0 && options != 1 && options != 2)){
        printf("\nError: option or mode arguments are not valid.\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

    // check maxiter to be more than zero
    if (maxiter <= 0) {
        printf("Error: argument maxiter must be more than zero!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of maxiter check

    // calculates y1 = f(a) and y2 =f(b)
    double fa = function_1_arg(expression, a);
    double fb = function_1_arg(expression, b);

    // if y1 and y2 have different signs, then we can use bisection method
    if (fa * fb < 0) {

        // initializing variables
        unsigned int iter = 1;
        double m;
        double x = 0;
        double ete_err;
        double ere_err;

        while (iter <= maxiter) {
            // calculate x
            x = (a * fb - b * fa) / (fb - fa);
            // evaluate the function at point x, y3 =f(x)
            double fc = function_1_arg(expression, x);

            if (mode) {
                printf("\nIteration number [#%d]: x = %10.7lf, f(x) = %.10e .\n", iter, x, fc);
            } // end if(mode)

            // if y3 and y1 have same signs, then substitute a by x and y1 by y3
            if (fc * fa > 0) {

                //calculate true error
                ete_err = fabs(a - x);

                // substitute
                a = x;
                fa = fc;

                // use illinois or anderson-bjork algorithm to improve regula falsi
                if (options){
                    m = 1 - fc / fa;
                    fb = options == 1 ? fb / 2 : (m > 1 ? fb * m : fb / 2);
                }

                if (mode) {
                    printf("In this iteration, a replaced by x, new range is [%lf, %lf].\n", a, b);
                } // end if(mode)

            } else if (fc * fb > 0) { // if y3 and y2 have same signs, then substitute b by x and y2 by y3

                //calculate true error
                ete_err = fabs(b - x);

                // substitute
                b = x;
                fb = fc;

                // use illinois or anderson-bjork algorithm to improve regula falsi
                if (options){
                    m = 1 - fc / fb;
                    fa = options == 1 ? fa / 2 : (m > 1 ? fa * m : fa / 2);
                }

                if (mode) {
                    printf("In this iteration, b replaced by x, new range is [%lf, %lf].\n", a, b);
                } // end if(mode)

            } else {
                if (mode) {
                    printf("In this iteration, f(x) = 0, so x is the root of function.\n\n");
                } // end if(mode)

                return x;
            } // end of if .. else if chained decisions

            //calculate relative error
            ere_err = fabs(ete_err / x);

            // Termination Criterion
            // if calculated error is less than estimated true error threshold
            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("\nIn this iteration, |x%d - x%d| < estimated true error [%.5e < %.5e],\n"
                           "so x is close enough to the root of function.\n\n", iter, iter - 1, ete_err, ete);
                } // end if(mode)

                return x;
            } // end of estimated true error check

            // if calculated error is less than estimated relative error threshold
            if (ere != 0 && ere_err < ere) {
                if (mode) {
                    printf("\nIn this iteration, |(x%d - x%d / x%d)| < estimated relative error [%.5e < %.5e],\n"
                           "so x is close enough to the root of function.\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(mode)

                return x;
            } // end of estimated relative error check

            // if y3 is less than tolerance error threshold
            if (tol != 0 && fabs(fc) < tol) {
                if (mode) {
                    printf("\nIn this iteration, |f(x)| < tolerance [%.5e < %.5e],\n"
                           "so x is close enough to the root of function.\n\n", fabs(fc), tol);
                } // end if(mode)

                return x;
            } // end of tolerance check

            iter++;
        } // end of while loop

        // answer didn't found
        if (mode) {
            if (ete == 0 && ere == 0 && tol == 0) {
                printf("\nWith maximum iteration of %d\n", maxiter);
            } else {
                printf("\nThe solution does not converge or iterations are not sufficient.\n");
            } // end of if ... else

            printf("the last calculated x is %lf\n", x);
        } // end if(mode)

        // set state to 0 (false)
        *state = 0;
        return x;

    } else { // if y1 and y2 have same signs, then we can't use false position method
        if (mode) {
            printf("Incorrect bracketing of function domain!\n"
                   "keep in mind that the inequality f(a) * f(b) < 0 must be correct\n"
                   "in order to use false position method.\n");
        }// end if(mode)

        *state = 0;
        return -1;
    } // end of if ... else
} // end of false position function
