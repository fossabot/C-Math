#include "bisection.h"
#include "functions.h"
#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0;
    int flag = 1;
    double a0, b0, ete, ere, tol;

    printf("\t\t\t      Root Finder\n\t\t\t   Bisection Method\n\t\tIRIBU Numerical"
           " Analysis Course Project\n\t\t   Student: Mohammad Mahdi Baghbani\n\n");
    printf("\nEnter the function you want to solve [example]: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the the range of function domain rang [a, b]\n");
    printf("Enter a:\n");
    fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

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

    double x = bisection(expression, a0, b0, ete, ere, tol, maxiter, mode, &flag);

    if (flag) {
        printf("\nThis method solved the equation for x= %lf in domain range of [%6.3lf, %6.3lf].\n\n", x, a0, b0);
    } // end of if flag

    Exit();

    if (flag) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    } // end of if flag

} // end of main


double bisection(const char *expression, double a, double b, double ete, double ere, double tol, int maxiter, int mode,
                 int *state) {

    double fa = function(a, expression);
    double fb = function(b, expression);

    if (fa * fb < 0) {

        int iter = 1;
        double c = 0;
        double ete_err;
        double ere_err;

        while (iter <= maxiter) {

            c = (a + b) / 2;
            double fc = function(c, expression);

            if (mode) {
                printf("\nIteration number: %3d, c = %10.7lf, f(c) = %.10e  .\n", iter, c, fc);
            } // end if(mode)

            if (fc * fa > 0) {
                ete_err = fabs(b - c);
                ere_err = fabs(ete_err / c);
                a = c;
                fa = fc;

                if (mode) {
                    printf("In this iteration, a replaced by c, new range is [%lf, %lf].\n", a, b);
                } // end if(mode)

            } else if (fc * fb > 0) {
                ete_err = fabs(b - c);
                ere_err = fabs(ete_err / c);
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

            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("\nIn this iteration, |c(%d) - c(%d)| < estimated true error [%.5e < %.5e],"
                           "so c is close enough to the root of function\n\n", iter, iter - 1, ete_err, ete);
                } // end if(mode)
                return c;
            } // end of estimated true error check

            if (ere != 0 && ere_err < ere) {
                if (mode) {
                    printf("\nIn this iteration, |(c(%d) - c(%d) / c(%d))| < estimated relative error [%.5e < %.5e"
                           "], so c is close enough to the root of function\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(mode)
                return c;
            } // end of estimated relative error check

            if (tol != 0 && fabs(fc) < tol) {
                if (mode) {
                    printf("\nIn this iteration, |f(c)| < tolerance [%.5e < %.5e],"
                           " so c is close enough to the root of function\n\n", fabs(fc), tol);
                } // end if(mode)
                return c;
            } // end of tolerance check

            iter++;
        } // end of while loop

        if (ete == 0 && ere == 0 && tol == 0) {
            printf("\nWith maximum iteration of %d\n", maxiter);
        } else {
            printf("\nThe solution does not converge or iterations are not sufficient\n");
        }
        printf("the last calculated c is %lf\n", c);
        *state = 0;
        return -1;
    } else {
        printf("Incorrect bracketing of function domain!\n keep in mind that"
               " the equation f(a) * f(b) < 0 must be correct\n in order to use Bisection method\n");
        *state = 0;
        return -1;
    } // end of if ... else

} // end of bisection function