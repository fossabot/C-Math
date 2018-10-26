#include "fixedPoint.h"
#include "../lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    char expression[INPUT_SIZE];
    char x0_c[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0;
    int flag = 1;
    double x0, ete, ere, tol;

    printf("\t\t\t      Root Finder\n\t\t\t  Fixed point Method\n\t\tIRIBU Numerical"
           " Analysis Course Project\n\t\t   Student: Mohammad Mahdi Baghbani\n\n");

    printf("\nEnter the function you want to solve (example: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the starting point (x0):\n");
    fgets(x0_c, sizeof(x0_c), stdin);
    x0 = strtod(x0_c, &ptr);

    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    printf("Enter the maximum iteration limit (must be positive number):\n");
    fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    if (maxiter <= 0) {
        printf("Invalid value for maximum iteration limit!\n");
        Exit();
        exit(EXIT_FAILURE);
    }// end of if maxiter

    printf("Do you want to see steps? enter 1 for yes and 0 for no:\n");
    fgets(mode_c, sizeof(mode_c), stdin);
    mode = strtol(mode_c, &ptr, 10);

    if (mode != 0 && mode != 1) {
        printf("Invalid value for mode!\n");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if mode

    double x = fixedPoint(expression, x0, ete, ere, tol, maxiter, mode, &flag);

    if (flag) {
        printf("\nThis method solved the equation for x= %lf .\n\n", x);
    } // end of if flag

    Exit();

    if (flag) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    } // end of if flag

} // end of main


double fixedPoint(const char *expression, double x0, double ete, double ere, double tol, int maxiter, int mode,
                  int *state) {

    int iter = 1;
    double x = x0;
    double fx = function(x, expression);
    double xNew;
    double gx;
    double ete_err;
    double ere_err;

    while (iter <= maxiter) {

        gx = fx + x;
        xNew = gx;

        if (mode) {
            printf("Iteration number: %d, x = %lf, f(x) = %lf, g(x) = %lf\n", iter, x, fx, gx);
        }

        ete_err = fabs(xNew - x);
        ere_err = fabs(ete_err / x);

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

        if (tol != 0 && fabs(fx) < tol) {
            if (mode) {
                printf("\nIn this iteration, |f(x(%d))| < tolerance [%.5e < %.5e],\n"
                       "so x is close enough to the root of function\n\n", iter, fabs(fx), tol);
            } // end if(mode)

            return x;
        } // end of tolerance check

        x = xNew;
        fx = function(x, expression);
        iter++;
    } // end of while loop

    if (ete == 0 && ere == 0 && tol == 0) {
        printf("\nWith maximum iteration of %d\n", maxiter);
    } else {
        printf("\nThe solution does not converge or iterations are not sufficient\n");
    }
    printf("the last calculated x is %lf\n", x);
    *state = 0;
    return -1;

} // end of fixed point function
