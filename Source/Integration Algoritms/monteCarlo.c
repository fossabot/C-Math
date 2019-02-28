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
    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE], options_c[INPUT_SIZE], verbose_c[INPUT_SIZE];
    char *ptr;
    int verbose = 0, n, options;
    double a0, b0;

    printf("\t\t\t\tIntegral Calculator\n"
           "\t\t\t\t     Monte Carlo\n");

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

    // get type of monte carlo integration
    printf("Select type of Monte Carlo integration {Random points: 0 , Random rectangles: 1}:\n");
    fgets(options_c, sizeof(options_c), stdin);
    options = strtol(options_c, &ptr, 10);

    // check options value
    if (options != 0 && options != 1) {
        printf("Wrong type number! you have to enter 0 or 1 .\n");
        Exit();
        return EXIT_FAILURE;
    }

    // get number of points or rectangles
    switch (options){
        case 0:
            printf("Enter the number of random points for integration:\n");
            break;
        case 1:
            printf("Enter the number of random rectangles for integration:\n");
            break;
    } // end of switch
    fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        printf("Number of rectangles must be more than zero!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check

    printf("Do you want to see steps? {0: no, 1: yes}:\n");
    fgets(verbose_c, sizeof(verbose_c), stdin);
    verbose = strtol(verbose_c, &ptr, 10);

    // check verbose value
    if (verbose != 0 && verbose != 1) {
        printf("Invalid value! you must enter either 0 or 1\n");
        Exit();
        return EXIT_FAILURE;
    } // end of if verbose

    // show something while calculating the area
    if (!verbose && n >= 5000000) {
        printf("\nCalculating...\n");
    } // end of if

    // calculation
    double area = monteCarloIntegration(expression, a0, b0, (unsigned int) n, (unsigned int) options, verbose);

    // show result
    printf("\nEstimated area under the function %sin the interval [%lf, %lf] is equal to: %lf.\n\n", expression,
           a0, b0, area);
    Exit();
    return EXIT_SUCCESS;
} // end of main
