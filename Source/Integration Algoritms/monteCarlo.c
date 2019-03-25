#include "../Assets/Integration Algorithms/monteCarloIntegrationAlgorithm.h"
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
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], options_c[INPUT_SIZE], verbose_c[INPUT_SIZE],
            tryAgain_c[INPUT_SIZE];
    char *ptr;
    int verbose = 0, n = 0, options = 0, tryAgain = 0;
    double a0, b0;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t     Monte Carlo\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the function you want to integrate (example: x^2-3):\n");
    fgetsReturn = fgets(expression, sizeof(expression), stdin);

    INTERVAL: //LABEL for goto
    printf("Choose an interval [a, b]:\n");
    printf("Enter a:\n");
    fgetsReturn = fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgetsReturn = fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

    // check interval
    if (a0 == b0) {
        printf("Error: improper interval! 'a' and 'b' can't have same value.\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto INTERVAL;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } //end of interval check

    TYPE: //LABEL for goto
    // get type of monte carlo integration
    printf("Select type of Monte Carlo integration {Random points: 0 , Random rectangles: 1}:\n");
    fgetsReturn = fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);

    // check options value
    if (options != 0 && options != 1) {
        printf("Error: Wrong type number! you have to enter either 0 or 1 .\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto TYPE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    }

    P_R_NUMBER: //LABEL for goto
    // get number of points or rectangles
    switch (options){
        case 0:
            printf("Enter the number of random points for integration:\n");
            break;
        case 1:
            printf("Enter the number of random rectangles for integration:\n");
            break;
    } // end of switch
    // get number from user
    fgetsReturn = fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        switch (options) {
            case 0:
                printf("Error: number of points must be more than zero!\n");
                break;
            case 1:
                printf("Error: number of rectangles must be more than zero!\n");
                break;
        } // end of switch

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto P_R_NUMBER;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of ete check

    VERBOSE: //LABEL for goto
    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgetsReturn = fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if (verbose != 0 && verbose != 1) {
        printf("Error: invalid value for verbose!\n");

        // a chance to correct your mistake :)
        printf("\nDo you want to try again? {0: no, 1: yes}\n");
        fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
        tryAgain = strtol(tryAgain_c, &ptr, 10);
        if (tryAgain) {
            goto VERBOSE;
        } else {
            Exit(EXIT_FAILURE);
        } // end of if goto
    } // end of if verbose

    // show something while calculating the area
    if (!verbose && n >= 1000000) {
        printf("\nCalculating...\n");
    } // end of if

    // calculation
    double area = monteCarloIntegration(expression, a0, b0, (unsigned int) n, (unsigned int) options, verbose);

    // show result
    printf("\nEstimated area under the function %sin the interval [%lf, %lf] is equal to: %lf.\n\n", expression,
           a0, b0, area);

    // do you want to start again??
    printf("\nDo you want to start again? {0: no, 1: yes}\n");
    fgetsReturn = fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
    tryAgain = strtol(tryAgain_c, &ptr, 10);
    if (tryAgain) {
        goto START;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
    return EXIT_SUCCESS;
} // end of main
