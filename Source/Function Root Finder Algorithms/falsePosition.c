#include "../Assets/Function Root Finder Algorithms/falsePositionAlgorithm.h"
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
            tol_c[INPUT_SIZE], maxiter_c[INPUT_SIZE], verbose_c[INPUT_SIZE], algorithmType_c[INPUT_SIZE],
            tryAgain_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, verbose = 0, algorithmType = 0, tryAgain = 0, flag = 1;
    double a0, b0, ete, ere, tol;

    printf("\t\t\t\tRoot Finder\n"
           "\t\t\t  False Position Method\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the equation you want to solve (example: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    INTERVAL: //LABEL for goto
    printf("Choose an interval [a, b]:\n");
    printf("Enter a:\n");
    fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

    // check interval
    if (a0 == b0) {
        printf("Error: improper interval! 'a' and 'b' can't have same values.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto INTERVAL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    TYPE:
    printf("Select type of false position algorithm {Original: 0 , Illinois: 1 , Anderson-Bjork: 2}:\n");
    fgets(algorithmType_c, sizeof(algorithmType_c), stdin);
    algorithmType = strtol(algorithmType_c, &ptr, 10);

    // check algorithmType value
    if (algorithmType != 0 && algorithmType != 1 && algorithmType != 2) {
        printf("Error: invalid type. you must enter either 0 or 1 or 2.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto TYPE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    }

    ETE: //LABEL for goto
    printf("Enter the estimated true error limit: (enter 0 if you don't want to set an ETE limit):\n");
    fgets(ete_c, sizeof(ete_c), stdin);
    ete = strtod(ete_c, &ptr);

    // check ete to be positive
    if (ete < 0) {
        printf("Error: estimated true error limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto ETE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check

    ERE: //LABEL for goto
    printf("Enter the estimated relative error limit (enter 0 if you don't want to set an ERE limit):\n");
    fgets(ere_c, sizeof(ere_c), stdin);
    ere = strtod(ere_c, &ptr);

    // check ere to be positive
    if (ere < 0) {
        printf("Error: estimated relative error limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto ERE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto;
    } // end of ere check

    TOL: //LABEL for goto
    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    // check tol to be positive
    if (tol < 0) {
        printf("Error: estimated tolerance limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto TOL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto;
    } // end of ere check

    MAXITER: //LABEL for goto
    printf("Enter the maximum iteration limit (must be positive number):\n");
    fgets(maxiter_c, sizeof(maxiter_c), stdin);
    maxiter = strtol(maxiter_c, &ptr, 10);

    // check maximum iteration to be more than 0
    if (maxiter <= 0) {
        printf("Error: invalid value for maximum iteration limit!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto MAXITER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto;
    }// end of if maxiter

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    if (verbose != 0 && verbose != 1) {
        printf("Error: invalid value for verbose!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto VERBOSE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of if verbose

    // calculate
    double x = falsePosition(expression, a0, b0, ete, ere, tol, (unsigned int) maxiter, algorithmType, verbose, &flag);

    // if there was an answer
    if (flag) {
        printf("\nThis method solved the equation %sfor x= %lf in the interval [%lf, %lf].\n\n", expression, x, a0,
               b0);
    } else { // if no answer
        printf("\nThis method couldn't find the root of equation %sin given interval"
               "the last calculated value for x is: %lf.\n\n", expression, x);
    } // end of if flag

    // do you want to start again??
    printf("\nDo you want to start again? {0: no, 1: yes}\n");
    fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
    tryAgain = strtol(tryAgain_c, &ptr, 10);
    if (tryAgain) {
        goto START;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
} // end of main

