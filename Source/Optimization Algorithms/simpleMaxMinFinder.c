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
    char expression[INPUT_SIZE];
    char a[INPUT_SIZE], b[INPUT_SIZE], n_c[INPUT_SIZE];
    char *ptr;
    int n;
    double a0, b0;

    printf("\t\t\t\tOptimization Algorithm\n"
           "\t\t\t\t Simple MaxMin Finder\n");

    // getting required data from user
    printf("\nEnter the function you want to optimize (example: x^4-3*x^3+2):\n");
    fgets(expression, sizeof(expression), stdin);

    printf("Enter the range of function domain rang [a, b]:\n");
    printf("Enter a:\n");
    fgets(a, sizeof(a), stdin);
    a0 = strtod(a, &ptr);
    printf("Enter b:\n");
    fgets(b, sizeof(b), stdin);
    b0 = strtod(b, &ptr);

    printf("Enter the number of samples you want to create for optimization:\n");
    fgets(n_c, sizeof(n_c), stdin);
    n = strtol(n_c, &ptr, 10);

    // check n to be more than zero
    if (n <= 0) {
        printf("Number of samples must be more than zero!\n");
        Exit();
        return EXIT_FAILURE;
    } // end of ete check
    
    // calculation
    double *result = simpleMaxMinFinder(expression, a0, b0, (unsigned int) n);

    // show result
    printf("In domain range [%lf, %lf], maximum = %.5e, minimum = %.5e\n", a0, b0, result[0], result[1]);
    
    Exit();
    return EXIT_SUCCESS;
} // end of main

