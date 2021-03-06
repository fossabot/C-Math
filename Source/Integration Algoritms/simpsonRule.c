#include "../Assets/Integration Algorithms/simpsonRuleAlgorithm.h"
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
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], options_c[INPUT_SIZE], verbose_c[INPUT_SIZE],
            tryAgain_c[INPUT_SIZE];
    char *ptr;
    int n = 0, options = 0, verbose = 0, tryAgain = 0;
    double a0, b0;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t  Simpson's Rule\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the function you want to integrate (example: x^2-3):\n");
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
        printf("Error: improper interval! 'a' and 'b' can't have same valueS.\n");

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

    NUMBER: //LABEL for goto
    printf("Enter the number of sub-intervals you want to create for integration:\n");
    fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        printf("Error: number of sub-intervals must be more than zero!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto NUMBER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check

    // show warning message if n is odd
    if (n % 2 == 1) {
        printf("\nWARNING: choosing an odd number of sub intervals will decrease precision\n"
               "of the regular h/3 algorithm, it's recommended to use 3*h/8 algorithm in this case\n\n");
    } // end of warning

    TYPE: //LABEL for goto
    printf("Select type of Simpson's rule integration {h/3 rule: 0, 3*h/8 rule: 1}:\n");
    fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);
    // check verbose and options value

    if (options != 0 && options != 1) {
        printf("Error: wrong type number! you have to enter either 0 or 1.\n");

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

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
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

    // calculation
    double area = simpsonRule(expression, a0, b0, (unsigned int) n, options, verbose);

    // show result
    printf("\nEstimated area under the function %sin the interval [%lf, %lf] is equal to: %lf .\n\n", expression,
           a0, b0, area);

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

