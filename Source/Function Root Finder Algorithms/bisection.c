#include "../Assets/Function Root Finder Algorithms/bisectionAlgorithm.h"
#include "../Assets/Util/util.h"
#include "../Assets/Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>

void main() {
    /*
     * Interface of program, this interface will get necessary information from user.
     */

    // initializing variables
    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], verbose_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, verbose = 0, flag = 1;
    double a0, b0, ete, ere, tol;

    printf("\t\t\t\tRoot Finder\n"
           "\t\t\t     Bisection Method\n");

    // getting required data from user
    printf("\nEnter the equation you want to solve (example: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Choose an interval [a, b]:\n");
    printf("Enter a:\n");
    fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    // check ete to be positive
    if (ete < 0) {
        printf("Estimated true error limit must be a \"POSITIVE\" number!\n");
        Exit(EXIT_FAILURE);
    } // end of ete check

    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    // check ere to be positive
    if (ere < 0) {
        printf("Estimated relative error limit must be a \"POSITIVE\" number!\n");
        Exit(EXIT_FAILURE);
    } // end of ere check

    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    // check tol to be positive
    if (tol < 0) {
        printf("Estimated tolerance limit must be a \"POSITIVE\" number!\n");
        Exit(EXIT_FAILURE);
    } // end of ere check

    printf("Enter the maximum iteration limit (must be positive number):\n");
    fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    // check maximum iteration to be more than 0
    if (maxiter <= 0) {
        printf("Invalid value for maximum iteration limit!\n");
        Exit(EXIT_FAILURE);
    }// end of if maxiter

    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if (verbose != 0 && verbose != 1) {
        printf("Invalid value for verbose!\n");
        Exit(EXIT_FAILURE);
    } // end of if verbose

    // calculation
    double x = bisection(expression, a0, b0, ete, ere, tol, (unsigned int) maxiter, verbose, &flag);

    // if there was an answer
    if (flag) {
        printf("\nThis method solved the equation %sfor x= %lf in the interval [%lf, %lf].\n\n", expression, x, a0,
               b0);
    } else { // if no answer
        printf("\nThis method couldn't find the root of equation %sin given interval"
               "the last calculated value for x is: %lf .\n\n", expression, x);
    } // end of if flag

    Exit(EXIT_SUCCESS);
} // end of main

