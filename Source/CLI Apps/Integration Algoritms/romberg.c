#include "../../Library/Integration Algorithms/rombergAlgorithm.h"
#include "../../Library/Util/util.h"
#include "../../Library/Util/Configurations/asl_configurations.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
     * Interface of program, this interface will get necessary information from user.
     */

    // initializing variables
    char *fgetsReturn;
    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], k_c[INPUT_SIZE], tol_c[INPUT_SIZE], verbose_c[INPUT_SIZE],
            tryAgain_c[INPUT_SIZE];
    char *ptr;
    int verbose = 0, k = 0, tryAgain = 0;
    double a0, b0, tol;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t     Romberg\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the function you want to integrate (example: x^2-3):\n");
    fgetsReturn = fgets(expression, sizeof(expression), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a function.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto START;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    INTERVAL: //LABEL for goto
    printf("Choose an interval [a, b]:\n");

    A: //LABEL for goto
    printf("Enter a:\n");
    fgetsReturn = fgets(a, sizeof(a), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'a'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto A;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    a0 = strtod(a, &ptr);

    B: //LABEL for goto
    printf("Enter b:\n");
    fgetsReturn = fgets(b, sizeof(b), stdin);

    // check input
    if (*fgetsReturn == '\n') {
        printf("Error: you must enter a value for 'b'.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto B;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of input check

    b0 = strtod(b, &ptr);

    // check interval
    if (a0 == b0) {
        printf("Error: improper interval! 'a' and 'b' can't have same values.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto INTERVAL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    K_NUMBER: //LABEL for goto
    printf("Enter degree (k) of integration\n");
    // get number from user
    fgetsReturn = fgets(k_c, sizeof(k_c), stdin);
    k = strtol(k_c, &ptr, 10);

    // check k to be positive
    if (k < 0 || *fgetsReturn == '\n') {
        printf("Error: k can't be less than 0.\n");
        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto K_NUMBER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check

    TOL: //LABEL for goto
    printf("Enter the tolerance limit (enter 0 if you don't want to set a tolerance limit):\n");
    fgetsReturn = fgets(tol_c, sizeof(tol_c), stdin);
    tol = strtod(tol_c, &ptr);

    // check tol to be positive
    if (tol < 0 || *fgetsReturn == '\n') {
        printf("Error: estimated tolerance limit must be a \"POSITIVE\" number!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto TOL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ere check

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgetsReturn = fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if ((verbose != 0 && verbose != 1) || *fgetsReturn == '\n') {
        printf("Error: invalid value for verbose!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto VERBOSE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of if verbose

    // calculation
    double area = romberg(expression, a0, b0, (unsigned int) k, tol, verbose);

    // show result
    printf("\nEstimated area under the function %s"
           "in the interval [%lf, %lf] is equal to: %lf.\n\n", expression, a0, b0, area);

    // do you want to start again??
    printf("\nDo you want to start again? {0: no, 1: yes}\n");
    fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

    if (*fgetsReturn == '\n') {
        Exit(EXIT_FAILURE);
    } // end of if
    tryAgain = strtol(tryAgain_c, &ptr, 10);

    if (tryAgain) {
        goto START;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
    return EXIT_SUCCESS;
} // end of main