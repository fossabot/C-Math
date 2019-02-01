#include "../Assets/Optimization Algorithms/gradientAscentAlgorithm.h"
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
            maxiter_c[INPUT_SIZE], options_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int maxiter = 0, mode = 0, options;
    int flag = 1;
    double a0, b0, x0, gamma, ete, ere, result;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t    Gradient Ascent\n");

    // getting required data from user
    printf("\nEnter the function you want to optimize (example: x^4-3*x^3+2):\n");
    fgets(expression, sizeof(expression), stdin);

    // get type of gradient ascent optimization
    printf("Select type of Gradient Ascent Optimization {over whole interval: 0 , over custom interval [a, b]: 1}:\n");
    fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);

    // check options value
    if (options != 0 && options != 1) {
        printf("Wrong type number! you have to enter 0 or 1\n");
        Exit();
        return EXIT_FAILURE;
    }

    // get input based on selected type
    switch (options) {
        case 0:
            printf("Enter the starting point (x0):\n");
            fgets(x0_c, sizeof(x0_c), stdin);
            x0 = strtod(x0_c, &ptr);
            break;
        case 1:
            printf("Enter the range of function domain rang [a, b]:\n");
            printf("Enter a:\n");
            fgets(a, sizeof(a), stdin);
            a0 = strtod(a, &ptr);
            printf("Enter b:\n");
            fgets(b, sizeof(b), stdin);
            b0 = strtod(b, &ptr);
            break;
    } // end of switch

    printf("Enter the step size (aka gamma or learning rate): \n");
    fgets(gamma_c, sizeof(gamma_c), stdin);
    gamma = strtod(gamma_c, &ptr);

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

    printf("Enter the maximum iteration limit (must be a positive number):\n");
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

    // calculate with respect of selected type
    switch (options) {
        case 0:
            result = gradientAscent(expression, x0, ete, ere, gamma, (unsigned int) maxiter, mode, &flag);
            break;
        case 1:
            result = gradientAscentInterval(expression, a0, b0, ete, ere, gamma, (unsigned int) maxiter, mode);
            break;
    }

    // if there was an answer
    if (flag) {
        printf("\nThis method has found the maximum of the function at point x = %lf.\n\n", result);
        Exit();
        return EXIT_SUCCESS;
    } else { // if no answer
        printf("\nThis method didn't find the minimum of the function,"
               " the last calculated value for x is: %lf.\n\n", result);
        Exit();
        return EXIT_FAILURE;
    } // end of if flag

} // end of main
