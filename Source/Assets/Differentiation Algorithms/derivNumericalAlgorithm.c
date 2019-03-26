#include "derivNumericalAlgorithm.h"
#include "../Util/functions.h"
#include "../Util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double firstDerivative_1_arg(const char *expression, double x, double delta, int options) {
    /*
     * This function estimates a numerical derivative for a given one argument function at point x
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x            the point where derivative must be evaluated
     * delta        the dx for getting numerical derivative
     * options      which algorithm to use {0: BACKWARD_DIFFERENCE, 1: FORWARD_DIFFERENCE, 2: CENTRAL_DIFFERENCE}
     *
     */

    // check options
    if (options != BACKWARD_DIFFERENCE && options != FORWARD_DIFFERENCE && options != CENTRAL_DIFFERENCE) {
        printf("\nError: options argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    switch (options) {
        case BACKWARD_DIFFERENCE:
            // backward difference
            return (function_1_arg(expression, x) - function_1_arg(expression, x - delta)) / delta;
        case FORWARD_DIFFERENCE:
            // forward difference
            return (function_1_arg(expression, x + delta) - function_1_arg(expression, x)) / delta;
        case CENTRAL_DIFFERENCE:
            // central difference
            return (function_1_arg(expression, x + delta) - function_1_arg(expression, x - delta)) / (2 * delta);
    } // end of switch

    // it shouldn't reach this block of code, but however I write a return statement
    return EXIT_SUCCESS;
} // end of firstDerivative_1_arg

double centralFirstDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {
    /*
     * This function estimates a numerical derivative for a given one argument function at point x
     * with finite difference method
     *
     * ARGUMENTS:
     * expressions  the function expression, it must be a string array like "x^2+1"
     * x            the point where derivative must be evaluated
     * delta        the dx for getting numerical derivative
     * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6, 8}
     *
     * NOTE: it's good to use delta in range [1e-8, 1e-16] for this function
     * [double floating point accuracy IEEE 754-1985]
     * DX is defined DX = 1e-8 in _configurations.h
     *
     */

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY
        && accuracy != EIGHTH_ORDER_ACCURACY) {

        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double b1, b2, c1, c2, d1, d2, e1, e2;
    b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            b1 = 1.0 / 2;
            b2 = -b1;
            break;
        case FOURTH_ORDER_ACCURACY:
            b1 = 2.0 / 3;
            b2 = -b1;
            c1 = -1.0 / 12;
            c2 = -c1;
            break;
        case SIXTH_ORDER_ACCURACY:
            b1 = 3.0 / 4;
            b2 = -b1;
            c1 = -3.0 / 20;
            c2 = -c1;
            d1 = 1.0 / 60;
            d2 = -d1;
            break;
        case EIGHTH_ORDER_ACCURACY:
            b1 = 4.0 / 5;
            b2 = -b1;
            c1 = -1.0 / 5;
            c2 = -c1;
            d1 = 4.0 / 105;
            d2 = -d1;
            e1 = -1.0 / 280;
            e2 = -e1;
            break;
    } // end of switch

    return (e2 * function_1_arg(expression, x - 4 * delta) + d2 * function_1_arg(expression, x - 3 * delta) +
            c2 * function_1_arg(expression, x - 2 * delta) + b2 * function_1_arg(expression, x - 1 * delta) +
            b1 * function_1_arg(expression, x + 1 * delta) + c1 * function_1_arg(expression, x + 2 * delta) +
            d1 * function_1_arg(expression, x + 3 * delta) + e1 * function_1_arg(expression, x + 4 * delta)) /
           pow(delta, 1);
} // end of centralFirstDerivative_1_arg function

double centralSecondDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY
        && accuracy != EIGHTH_ORDER_ACCURACY) {

        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double a, b, c, d, e;
    a = b = c = d = e = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            a = -2;
            b = 1;
            break;
        case FOURTH_ORDER_ACCURACY:
            a = -5.0 / 2;
            b = 4.0 / 3;
            c = -1.0 / 12;
            break;
        case SIXTH_ORDER_ACCURACY:
            a = -49.0 / 18;
            b = 3.0 / 2;
            c = -3.0 / 20;
            d = 1.0 / 90;
            break;
        case EIGHTH_ORDER_ACCURACY:
            a = -205.0 / 72;
            b = 8.0 / 5;
            c = -1.0 / 5;
            d = 8.0 / 315;
            e = -1.0 / 560;
            break;
    } // end of switch

    return (e * function_1_arg(expression, x - 4 * delta) + d * function_1_arg(expression, x - 3 * delta) +
            c * function_1_arg(expression, x - 2 * delta) + b * function_1_arg(expression, x - 1 * delta) +
            a * function_1_arg(expression, x) +
            b * function_1_arg(expression, x + 1 * delta) + c * function_1_arg(expression, x + 2 * delta) +
            d * function_1_arg(expression, x + 3 * delta) + e * function_1_arg(expression, x + 4 * delta)) /
           pow(delta, 2);
} // end of centralSecondDerivative_1_arg function

double centralThirdDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY) {
        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double b1, b2, c1, c2, d1, d2, e1, e2;
    b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            b1 = -1.0;
            b2 = -b1;
            c1 = 1.0 / 2;
            c2 = -c1;
            break;
        case FOURTH_ORDER_ACCURACY:
            b1 = -13.0 / 8;
            b2 = -b1;
            c1 = 1.0;
            c2 = -c1;
            d1 = -1.0 / 8;
            d2 = -d1;
            break;
        case SIXTH_ORDER_ACCURACY:
            b1 = -61.0 / 30;
            b2 = -b1;
            c1 = 169.0 / 120;
            c2 = -c1;
            d1 = -3.0 / 10;
            d2 = -d1;
            e1 = 7.0 / 240;
            e2 = -e1;
            break;
    } // end of switch

    return (e2 * function_1_arg(expression, x - 4 * delta) + d2 * function_1_arg(expression, x - 3 * delta) +
            c2 * function_1_arg(expression, x - 2 * delta) + b2 * function_1_arg(expression, x - 1 * delta) +
            b1 * function_1_arg(expression, x + 1 * delta) + c1 * function_1_arg(expression, x + 2 * delta) +
            d1 * function_1_arg(expression, x + 3 * delta) + e1 * function_1_arg(expression, x + 4 * delta)) /
           pow(delta, 3);
} // end of centralThirdDerivative_1_arg function

double centralFourthDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY) {
        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double a, b, c, d, e;
    a = b = c = d = e = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            a = 6;
            b = -4;
            c = 1.0;
            break;
        case FOURTH_ORDER_ACCURACY:
            a = 28.0 / 3;
            b = -13.0 / 2;
            c = 2;
            d = -1.0 / 6;
            break;
        case SIXTH_ORDER_ACCURACY:
            a = 91.0 / 8;
            b = -122.0 / 15;
            c = 169.0 / 60;
            d = -2.0 / 5;
            e = 7.0 / 240;
            break;
    } // end of switch

    return (e * function_1_arg(expression, x - 4 * delta) + d * function_1_arg(expression, x - 3 * delta) +
            c * function_1_arg(expression, x - 2 * delta) + b * function_1_arg(expression, x - 1 * delta) +
            a * function_1_arg(expression, x) +
            b * function_1_arg(expression, x + 1 * delta) + c * function_1_arg(expression, x + 2 * delta) +
            d * function_1_arg(expression, x + 3 * delta) + e * function_1_arg(expression, x + 4 * delta)) /
           pow(delta, 4);
} // end of centralFourthDerivative_1_arg function

double centralFifthDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY) {
        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double b1, b2, c1, c2, d1, d2, e1, e2, f1, f2;
    b1 = b2 = c1 = c2 = d1 = d2 = e1 = e2 = f1 = f2 = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            b1 = 5.0 / 2;
            b2 = -b1;
            c1 = -2;
            c2 = -c1;
            d1 = 1.0 / 2;
            d2 = -d1;
            break;
        case FOURTH_ORDER_ACCURACY:
            b1 = 29.0 / 6;
            b2 = -b1;
            c1 = -13.0 / 3;
            c2 = -c1;
            d1 = 3.0 / 2;
            d2 = -d1;
            e1 = -1.0 / 6;
            e2 = -e1;
            break;
        case SIXTH_ORDER_ACCURACY:
            b1 = -323.0 / 48;
            b2 = -b1;
            c1 = -13.0 / 2;
            c2 = -c1;
            d1 = 87.0 / 32;
            d2 = -d1;
            e1 = -19.0 / 36;
            e2 = -e1;
            f1 = 13.0 / 288;
            f2 = -f1;
            break;
    } // end of switch

    return (f2 * function_1_arg(expression, x - 5 * delta) + e2 * function_1_arg(expression, x - 4 * delta) +
            d2 * function_1_arg(expression, x - 3 * delta) + c2 * function_1_arg(expression, x - 2 * delta) +
            b2 * function_1_arg(expression, x - 1 * delta) + b1 * function_1_arg(expression, x + 1 * delta) +
            c1 * function_1_arg(expression, x + 2 * delta) + d1 * function_1_arg(expression, x + 3 * delta) +
            e1 * function_1_arg(expression, x + 4 * delta) + f1 * function_1_arg(expression, x + 5 * delta)) /
           pow(delta, 5);
} // end of centralFifthDerivative_1_arg function

double centralSixthDerivative_1_arg(const char *expression, double x, double delta, int accuracy) {

    // check accuracy
    if (accuracy != SECOND_ORDER_ACCURACY && accuracy != FOURTH_ORDER_ACCURACY && accuracy != SIXTH_ORDER_ACCURACY) {
        printf("\nError: accuracy argument is not valid.\n");
        Exit(EXIT_FAILURE);
    } // end of if

    // initialize variables
    double a, b, c, d, e, f;
    a = b = c = d = e = f = 0;

    // central finite difference table
    switch (accuracy) {
        case SECOND_ORDER_ACCURACY:
            a = -20;
            b = 15;
            c = -6;
            d = 1;
            break;
        case FOURTH_ORDER_ACCURACY:
            a = -75.0 / 2;
            b = 29;
            c = -13;
            d = 3;
            e = -1.0 / 4;
            break;
        case SIXTH_ORDER_ACCURACY:
            a = -1023.0 / 20;
            b = 323.0 / 8;
            c = -39.0 / 2;
            d = 87.0 / 16;
            e = -19.0 / 24;
            f = 13.5 / 240;
            break;
    } // end of switch

    return (f * function_1_arg(expression, x - 5 * delta) + e * function_1_arg(expression, x - 4 * delta) +
            d * function_1_arg(expression, x - 3 * delta) + c * function_1_arg(expression, x - 2 * delta) +
            b * function_1_arg(expression, x - 1 * delta) +
            a * function_1_arg(expression, x) +
            b * function_1_arg(expression, x + 1 * delta) + c * function_1_arg(expression, x + 2 * delta) +
            d * function_1_arg(expression, x + 3 * delta) + e * function_1_arg(expression, x + 4 * delta) +
            f * function_1_arg(expression, x + 5 * delta)) /
           pow(delta, 6);
} // end of centralSixthDerivative_1_arg function