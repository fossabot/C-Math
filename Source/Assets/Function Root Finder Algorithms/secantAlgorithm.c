#include "secantAlgorithm.h"
#include "../Util/functions.h"

#include <stdio.h>
#include <math.h>

double secant(const char *expression, double x1, double x2, double ete, double ere, double tol, int maxiter, int mode,
              int *state) {

    int iter = 1;
    double fx1 = function_1_arg(expression, x1);
    double fx2 = function_1_arg(expression, x2);
    double xNew = 0;
    double fxNew;
    double ete_err;
    double ere_err;

    while (iter <= maxiter) {
        xNew = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
        fxNew = function_1_arg(expression, xNew);

        if (mode) {
            printf("Iteration number: %d, x(%d) = %lf, f(x(%d)) = %lf\n\n", iter, iter, xNew, iter, fxNew);
        } // end of if mode

        ete_err = fabs(xNew - x2);
        ere_err = fabs((xNew - x2) / x2);

        if (ete != 0 && ete_err < ete) {
            if (mode) {
                printf("\nIn this iteration, |x(%d) - x(%d)| < estimated true error [%.5e < %.5e],\n"
                       "so x is close enough to the root of function\n\n", iter, iter - 1, ete_err, ete);
            } // end if(mode)

            return xNew;
        } // end of estimated true error check

        if (ere != 0 && ere_err < ere) {
            if (mode) {
                printf("\nIn this iteration, |(x(%d) - x(%d) / x(%d))| < estimated relative error [%.5e < %.5e"
                       "],\nso x is close enough to the root of function\n\n", iter, iter - 1, iter, ere_err, ere);
            } // end if(mode)

            return xNew;
        } // end of estimated relative error check

        if (tol != 0 && fabs(fxNew) < tol) {
            if (mode) {
                printf("\nIn this iteration, |f(x(%d))| < tolerance [%.5e < %.5e],\n"
                       "so x is close enough to the root of function\n\n", iter, fabs(fxNew), tol);
            } // end if(mode)

            return xNew;
        } // end of tolerance check

        x1 = x2;
        fx1 = fx2;
        x2 = xNew;
        fx2 = fxNew;
        iter++;

    } // end of while loop

    if (ete == 0 && ere == 0 && tol == 0) {
        printf("\nWith maximum iteration of %d\n", maxiter);
    } else {
        printf("\nThe solution does not converge or iterations are not sufficient\n");
    }
    printf("the last calculated x is %lf\n", xNew);
    *state = 0;
    return -1;

} // end of secant function