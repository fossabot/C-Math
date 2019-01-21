#include "functions.h"
#include "util.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

double function_1_arg(const char *expression, double value) {

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
        // Show the user where the error is at
        printf("%s", expression);
        printf("%*s^\nError near here\n", err - 1, "");
        Exit();
        exit(EXIT_FAILURE);
    }
}// end of function


double firstDerivative_1_arg(const char *expression, double x, double delta) {
    return (function_1_arg(expression, x + delta) - function_1_arg(expression, x - delta)) / (2 * delta);
}
