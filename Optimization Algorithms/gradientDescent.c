#include "gradientDescent.h"
#include "../Lib/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    char expression[INPUT_SIZE];
    char x0_c[INPUT_SIZE], gamma_c[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE], maxiter_c[INPUT_SIZE],
            mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0;
    int flag = 1;
    double x0, gamma, ete, ere;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t   Gradient Descent\n");

    printf("\nEnter the function you want to solve (example: x^4-3*x^3+2):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the starting point (x0):\n");
    fgets(x0_c, sizeof(x0_c), stdin);
    x0 = strtod(x0_c, &ptr);

    printf("Enter the step size (aka gamma or learning rate): \n");
    fgets(gamma_c, sizeof(gamma_c), stdin);
    gamma = strtod(gamma_c, &ptr);

    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    if (ete < 0){
        printf("Estimated true error limit must be a \"POSITIVE\" number!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check

    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    if (ere < 0){
        printf("Estimated relative error limit must be a \"POSITIVE\" number!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ere check

    printf("Enter the maximum iteration limit (must be a positive number):\n");
    fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    if (maxiter <= 0) {
        printf("Invalid value for maximum iteration limit!\n");
        Exit();
        return EXIT_FAILURE;
    }// end of if maxiter

    printf("Do you want to see steps? enter 1 for yes and 0 for no:\n");
    fgets(mode_c, sizeof(mode_c), stdin);
    mode = strtol(mode_c, &ptr, 10);

    if (mode != 0 && mode != 1) {
        printf("Invalid value for mode!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of if mode

    double x = gradientDescent(expression, x0, ete, ere, gamma, maxiter, mode, &flag);

    if (flag) {
        printf("\nThis method has found the minimum of the function at point X = %lf.\n\n", x);
        Exit();
        return EXIT_SUCCESS;
    } else {
        Exit();
        return EXIT_FAILURE;
    } // end of if flag

} // end of main


double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, int maxiter, int mode,
                       int *state) {
    /*
     * Gradient descent is a first-order iterative optimization algorithm for finding the minimum of a function.
     * To find a local minimum of a function using gradient descent, one takes steps proportional to the negative of
     * the gradient (or approximate gradient) of the function at the current point.
     */

    int iter = 0;
    double ete_err;
    double ere_err;
    double past_x;

    while(iter < maxiter) {
        past_x = x0;
        x0 -= firstDerivative(past_x, DX, expression) * gamma;

        ete_err = fabs(past_x - x0);
        ere_err = fabs(ete_err / x0);

        if (mode){
            printf("\nIn this iteration [#%d], X = %lf and estimated true error = %.5e\n"
                   "and estimated relative error = %.5e,\n", iter, x0, ete_err, ere_err);
        } // end if(mode)

        if (ete != 0 && ete_err < ete) {
            if (mode) {
                printf("\nIn this iteration the calculated estimated true error is less than the threshold\n"
                       "(estimated true error) %.5e < %.5e (threshold)\n"
                       "so the calculated X is the minimum of the function\n", ete_err, ete);
            } // end if(mode)

            return x0;
        } // end of estimated true error check

        if (ere != 0 && ere_err < ere) {
            if (mode) {
                printf("\nIn this iteration the calculated estimated real error is less than the threshold\n"
                       "(estimated real error) %.5e < %.5e (threshold)\n"
                       "so the calculated X is the minimum of the function\n", ere_err, ere);
            } // end if(mode)

            return x0;
            } // end of estimated relative error check

        iter++;
    } // end of while loop

    if (ete == 0 && ere == 0) {
        printf("\nWith maximum iteration of %d\n", maxiter);
    } else {
        printf("\nThe solution does not converge or iterations are not sufficient\n");
    } // end of if ... else

    printf("the last calculated c is %lf\n", x0);
    *state = 0;
    return -1;
} // end of gradientDescent function