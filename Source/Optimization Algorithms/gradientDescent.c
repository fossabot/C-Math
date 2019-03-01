#include "../Assets/Optimization Algorithms/gradientDescentAlgorithm.h"
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
    char a[INPUT_SIZE], b[INPUT_SIZE], x0_c[INPUT_SIZE], gamma_c[INPUT_SIZE], ete_c[INPUT_SIZE], ere_c[INPUT_SIZE],
            maxiter_c[INPUT_SIZE], options_c[INPUT_SIZE], verbose_c[INPUT_SIZE], tryAgain_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, options = 0, verbose = 0, tryAgain = 0, flag = 1;;
    double a0, b0, x0, gamma, ete, ere, result;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t   Gradient Descent\n");

    START: //LABEL for goto
    // getting required data from user
    printf("\nEnter the function you want to optimize (example: x^4-3*x^3+2):\n");
    fgets(expression, sizeof(expression), stdin);

    TYPE: //LABEL for goto
    // get type of gradient ascent optimization
    printf("Select type of Gradient Descent Optimization {nearest extremum to x0: 0 , "
           "over custom interval [a, b]: 1}:\n");
    fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);

    // check options value
    if (options != 0 && options != 1) {
        printf("Error: wrong type number! you have to enter either 0 or 1\n");

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

    INTERVAL: //LABEL for goto
    // get input based on selected type
    switch (options) {
        case 0:
            printf("Enter the starting point (x0):\n");
            fgets(x0_c, sizeof(x0_c), stdin);
            x0 = strtod(x0_c, &ptr);
            break;
        case 1:
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
            break;
    } // end of switch

    printf("Enter the step size (aka gamma or learning rate): \n");
    fgets(gamma_c, sizeof(gamma_c), stdin);
    gamma = strtod(gamma_c, &ptr);

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
        } // end of if goto
    } // end of ere check

    MAXITER: //LABEL for goto
    printf("Enter the maximum iteration limit (must be a positive number):\n");
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
        } // end of if goto
    }// end of if maxiter

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

    // calculate with respect of selected type
    switch (options) {
        case 0:
            result = gradientDescent(expression, x0, ete, ere, gamma, (unsigned int) maxiter, verbose, &flag);
            break;
        case 1:
            result = gradientDescentInterval(expression, a0, b0, ete, ere, gamma, (unsigned int) maxiter, verbose);
            break;
    }

    // if there was an answer
    if (flag) {
        printf("\nThis method has found the minimum of the function %sat point x = %lf .\n\n", expression, result);
    } else { // if no answer
        printf("\nThis method didn't find the minimum of the function %s"
               "the last calculated value for x is: %lf .\n\n", expression, result);
    } // end of if flag

    // do you want to start again??
    printf("Do you want to start again? {0: no, 1: yes}\n");
    fgets(tryAgain_c, sizeof(tryAgain_c), stdin);
    tryAgain = strtol(tryAgain_c, &ptr, 10);
    if (tryAgain) {
        goto START;
    } else {
        Exit(EXIT_SUCCESS);
    } // end of if goto
} // end of main
