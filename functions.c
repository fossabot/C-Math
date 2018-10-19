#include "functions.h"
#include "tinyexpr.h"
#include <stdio.h>
#include <stdlib.h>

double function(double value, const char *expression) {

    double x;
    int err;
    te_variable vars[] = {{"x", &x}};
    te_expr *equation = te_compile(expression, vars, 1, &err);
    if (equation) {
        x = value;
        const double result = te_eval(equation);
        te_free(equation);
        return result;
    } else {
        /* Show the user where the error is at. */
        printf("\t%*s^\nError near here", err - 1, "");
        printf("try again!\n");
        Exit();
        exit(EXIT_FAILURE);
    }
}// end of function


double firstDerivative(int x, double delta, const char *expression) {
    return (function(x + delta, expression) - function(x - delta, expression)) / 2 * delta;
}

void Exit(void) {
    printf("\nPress any key to exit\n");
    getc(stdin);
} // end of exit