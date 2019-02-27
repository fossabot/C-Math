#include "../Assets/Integration Algorithms/trapezoidRuleAlgorithm.h"
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
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], mode_c[INPUT_SIZE];
    char *ptr;
    int mode = 0, n;
    double a0, b0;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t  Trapezoid Rule\n");

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

    printf("Enter the number of trapezoids you want to create for integration:\n");
    fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        printf("Number of trapezoids must be more than zero!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check

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
    double area = trapezoidRule(expression, a0, b0, (unsigned int) n, mode);

    // show result
    printf("\nEstimated area under the function %s , in domain range of [%lf, %lf] is equal to: %lf .\n\n", expression,
           a0, b0, area);
    Exit();
    return EXIT_SUCCESS;
} // end of main

