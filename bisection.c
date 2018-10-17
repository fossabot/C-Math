#include "bisection.h"
#include <stdio.h>
#include <math.h>

int main() {
    int *state;
    *state = 1;
    double t = bisection(-0.95, 10, 0.000001, 0, 0, 30, 1, state);
    printf("x= %lf", t);
} // end of main

double function(double x) {
    return x - pow(5, 0.5);
} // end of function

double bisection(double a, double b, double ete, double ere, double tol, int maxiter, int mode, int *state) {

    double a0 = a;
    double b0 = b;
    double fa = function(a);
    double fb = function(b);

    if (fa * fb < 0) {

        int iter = 1;
        double ete_err;
        double ere_err;

        while (iter <= maxiter) {

            double c = (a + b) / 2;
            double fc = function(c);

            if (mode) {
                printf("Iteration number: %3d, c = %10.7lf, f(c) = %10.7lf .\n", iter, c, fc);
            } // end if(mode)

            if (fc * fa > 0) {
                ete_err = fabs(b - c);
                ere_err = fabs(ete_err / c);
                a = c;
                fa = fc;

                if (mode) {
                    printf("In this iteration, a replaced by c, new range is [%lf, %lf].\n\n", a, b);
                } // end if(mode)

            } else if (fc * fb > 0) {
                ete_err = fabs(b - c);
                ere_err = fabs(ete_err / c);
                b = c;
                fb = fc;

                if (mode) {
                    printf("In this iteration, b replaced by c, new range is [%lf, %lf].\n\n", a, b);
                } // end if(mode)

            } else {
                if (mode) {
                    printf("In this iteration, f(c) = 0, so c is the root of function in range [%lf, %lf].\n\n", a0,
                           b0);
                } // end if(mode)

                return c;

            } // end of if .. else if chained decisions

            if (ete != 0 && ete_err < ete) {
                if (mode) {
                    printf("In this iteration, |c(%d) - c(%d)| < estimated true error [%10.7lf < %10.7lf],"
                           "so c is enough close to the root of function\n\n", iter, iter - 1, ete_err, ete);
                } // end if(mode)

                return c;

            } // end of estimated true error check

            if (ere != 0 && ere_err < ere) {

                if (mode) {
                    printf("In this iteration, |(c(%d) - c(%d) / c(%d))| < estimated relative error [%10.7lf < %10.7lf"
                           "], so c is enough close to the root of function\n\n", iter, iter - 1, iter, ere_err, ere);
                } // end if(mode)

                return c;

            } // end of estimated relative error check

            if (tol != 0 && fabs(fc) < tol) {

                if (mode) {
                    printf("In this iteration, |f(c)| < tolerance [%10.7lf < %10.7lf],"
                           "so c is enough close to the root of function\n\n", fabs(fc), tol);
                } // end if(mode)

                return c;

            } // end of tolerance check

            iter++;

        } // end of while loop

        *state = 0;
        return -2;

    } else {
        printf("Incorrect bracketing of function domain! keep in mind that"
               " the equation f(a) * f(b) < 0 must be correct in order to use Bisection method\n");
        *state = 0;
        return -1;
    } // end of if ... else

} // end of bisection function
