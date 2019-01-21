#include "../Assets/Function Root Finder Algorithms/newtonRaphsonAlgorithm.h"
#include "../Assets/Util/util.h"
#include "../Assets/Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
     * Interface of program, this interface will get necessary information from user.
     */

    // initializing variables
    char expression[INPUT_SIZE];
    char x0_c[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0;
    int flag = 1;
    double x0, ete, ere, tol;

    printf("\t\t\t\tRoot Finder\n"
           "\t\t\t  Newton-Raphson Method");

    // getting required data from user
    printf("\nEnter the function you want to solve (example: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the starting point (x0):\n");
    fgets(x0_c, sizeof(x0_c), stdin);
    x0 = strtod(x0_c, &ptr);

    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    // check ete to be positive
    if (ete < 0) {
        printf("Estimated true error limit must be a \"POSITIVE\" number!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check

    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    // check ere to be positive
    if (ere < 0) {
        printf("Estimated relative error limit must be a \"POSITIVE\" number!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ere check

    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    // check tol to be positive
    if (tol < 0) {
        printf("Estimated tolerance limit must be a \"POSITIVE\" number!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ere check

    printf("Enter the maximum iteration limit (must be positive number):\n");
    fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    // check maximum iteration to be more than 0
    if (maxiter <= 0) {
        printf("Invalid value for maximum iteration limit!\n");
        Exit();
        return EXIT_FAILURE;
    }// end of if maxiter

    printf("Do you want to see steps? enter 1 for yes and 0 for no:\n");
    fgets(mode_c, sizeof(mode_c), stdin);
    mode = strtol(mode_c, &ptr, 10);

    // check mode value
    if (mode != 0 && mode != 1) {
        printf("Invalid value for mode!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of if mode

    // calculation
    double x = newtonRaphson(expression, x0, ete, ere, tol, maxiter, mode, &flag);

    // if there was an answer
    if (flag) {
        printf("\nThis method solved the equation for x= %lf .\n\n", x);
        Exit();
        return EXIT_SUCCESS;
        // if no answer
    } else {
        printf("\nThis method couldn't find the root of function\n"
               "the last calculated value for X is: %lf.\n\n", x);
        Exit();
        return EXIT_FAILURE;
    } // end of if flag

} // end of main
