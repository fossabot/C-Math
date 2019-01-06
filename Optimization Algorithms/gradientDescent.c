#include "gradientDescent.h"
#include "../Lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    char expression[INPUT_SIZE];
    char x0_c[INPUT_SIZE], gamma_c[INPUT_SIZE], error_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0;
    int flag = 1;
    double x0, gamma, error;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t   Gradient Descent\n"
           "\t\t\tIRIBU Numerical Analysis Course Project\n "
           "\n\t\t\t\t       Writers:\n"
           "\t\t\t\tErfan Akbari 9611522904\n"
           "\t\t\t\tSamin Makin 9611522926\n"
           "\n\t\t\t\t     Maintainer:\n"
           "\t\t\t   Mohammad Mahdi Baghbani 9611522904\n\n");

    printf("\nEnter the function you want to solve (example: x^4-3*x^3+2):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the starting point (x0):\n");
    fgets(x0_c, sizeof(x0_c), stdin);
    x0 = strtod(x0_c, &ptr);

    printf("Enter the error limit (most be a positive number):\n");
    fgets(error_c, sizeof(error_c), stdin);
    error = strtod(error_c, &ptr);

    if (error <= 0) {
        printf("Invalid value for maximum iteration limit!\n");
        Exit();
        exit(EXIT_FAILURE);
    }// end of if error value check

    printf("Enter the step size (aka gamma or learning rate): \n");
    fgets(gamma_c, sizeof(gamma_c), stdin);
    gamma = strtod(gamma_c, &ptr);

    printf("Enter the maximum iteration limit (must be a positive number):\n");
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

    double x = gradientDescent(expression, x0, error, gamma, maxiter, mode, &flag);

    if (flag) {
        printf("\nThis method has found the minimum of the function at point X = %lf.\n\n", x);
        Exit();
        return EXIT_SUCCESS;
    } else {
        Exit();
        return EXIT_FAILURE;
    } // end of if flag

} // end of main


double gradientDescent(const char *expression, double x0, double error, double gamma, int maxiter, int mode, int *state) {

    double c_error;
    int iter = 0;
    double p_error;

    while(iter < maxiter) {
        p_error = x0;
        x0 -= firstDerivative(p_error, 1e-6, expression) * gamma;
        c_error = fabs(p_error - x0);

        if (mode){
            printf("\nIn this iteration [#%d], X = %f and error = %f,\n", iter, x0, c_error);
        } // end if(mode)

        if (c_error < error){
            if (mode){
                printf("\nIn this iteration [#%d], X = %f and error = %f,\nso the calculated X is the minimum of the "
                       "function", iter, x0, c_error);
            } // end if(mode)

            return x0;
        } // end if(error < c_error)

        iter++;
    } // end while

    printf("\nThe solution does not converge or iterations are not sufficient\n");
    printf("the last calculated X is %lf\n", x0);
    *state = 0;
    return -1;

}