#include "riemannSumAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdlib.h>
#include <stdio.h>

double riemannSum(const char *expression, double a, double b, unsigned int n, int option, int mode) {

    if ((mode != 0 && mode != 1) || (option != 0 && option != 1 && option != 2)){
        printf("\nError: option or mode arguments are not valid\n");
        Exit();
        exit(EXIT_FAILURE);
    }

    double area = 0, x;
    double c = (b - a) / n;
    int scale = (option == 1) ? 1 : 0;

    for (int i = scale; i <= n - 1 + scale; ++i) {
        if (option != 2) {
            x = a + i * c;
        } else {
            x = a + c * (2 * i + 1) / 2;
        }
        area += function_1_arg(expression, x);
    }

    area *= c;

    return area;

} // end of riemann sum function
