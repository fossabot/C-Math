#include "functions.h"
#include "util.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

double function_1_arg(const char *expression, double valueX) {
    /*
     * This function takes an expression of a one argument function "f(x)"
     * and a value, then it will calculate y = f(value)
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * value        the point where the function must be evaluated
     */

    // initializing variables
    double x;
    int err;

    // initializing vars[] and compile string expression into a te_expr object
    te_variable vars[] = {{"x", &x}};
    te_expr *equation = te_compile(expression, vars, 1, &err);

    if (equation) {
        x = valueX;
        const double result = te_eval(equation);
        te_free(equation);
        return result;
    } else { // Show the user where the error is at
        printf("%s", expression);
        printf("%*s^\nError near here\n", err - 1, "");
        Exit();
        exit(EXIT_FAILURE);
    } // end of if

}// end of function_1_arg


double firstDerivative_1_arg(const char *expression, double x, double delta) {
    /*
     * This function estimates a numerical derivative for a given one argument function at x
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x            the point where derivative must be evaluated
     * delta        the dx for getting numerical derivative
     */

    return (function_1_arg(expression, x + delta) - function_1_arg(expression, x - delta)) / (2 * delta);
} // end of firstDerivative_1_arg
