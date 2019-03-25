#include "../Assets/Optimization Algorithms/simpleMaxMinFinderAlgorithm.h"
#include "../Assets/Util/util.h"
#include "../Assets/Util/_configurations.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    /*
     * Interface of program, this interface will get necessary information from user.
     */

    // initializing variables
    char *fgetsReturn;
    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], tryAgain_c[INPUT_SIZE];
    char *ptr;
    int n = 0, tryAgain = 0;
    double a0, b0;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t Simple MaxMin Finder\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the function you want to optimize (example: x^4-3*x^3+2):\n");
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

    NUMBER: //LABEL for goto
    printf("Enter the number of samples you want to create for optimization:\n");
    fgetsReturn = fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0 || *fgetsReturn == '\n') {
        printf("Error: number of samples must be more than zero!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);

        if (*fgetsReturn == '\n') {
            Exit(EXIT_FAILURE);
        } // end of if
        tryAgain = strtol(tryAgain_c, &ptr, 10);

        if (tryAgain) {
            goto NUMBER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check
    
    // calculation
    double *result = simpleMaxMinFinder(expression, a0, b0, (unsigned int) n);

    // show result
    printf("In domain range [%g, %g], x maximum = %g, x minimum = %g\n", a0, b0, result[0], result[1]);


    // do you want to start again??
    printf("Do you want to start again? {0: no, 1: yes}\n");
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

