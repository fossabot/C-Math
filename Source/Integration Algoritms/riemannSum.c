#include "../Assets/Integration Algorithms/riemannSumAlgorithm.h"
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
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], options_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int mode = 0, n, options;
    double a0, b0;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t Riemann Sum Rule\n");

    // getting required data from user
    printf("\nEnter the function you want to integrate (example: x^2-3):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Choose an interval [a, b]:\n");
    printf("Enter a:\n");
    fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

    printf("Enter the number of rectangles you want to create for integration:\n");
    fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        printf("Number of rectangles must be more than zero!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check

    printf("Select type of Riemann integration rule {Left point: 0, Right point: 1, Mid point: 2}:\n");
    fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);

    // check options value
    if (options != 0 && options != 1 && options != 2) {
        printf("Wrong type number! you have to enter 0 or 1 or 2\n");
        Exit();
        return EXIT_FAILURE;
    }

    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgets(mode_c, sizeof(mode_c), stdin);
    mode = strtol(mode_c, &ptr, 10);

    // check mode value
    if (mode != 0 && mode != 1) {
        printf("Invalid value for mode!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of if mode

    // calculation
    double area = riemannSum(expression, a0, b0, (unsigned int) n, options, mode);

    // show result
    printf("\nEstimated area under the function %s , in domain range of [%lf, %lf] is equal to: %lf .\n\n", expression,
           a0, b0, area);
    Exit();
    return EXIT_SUCCESS;
} // end of main

