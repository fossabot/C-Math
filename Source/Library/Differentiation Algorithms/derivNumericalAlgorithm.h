#ifndef C_MATH_DERIVNUMERICALALGORITHM_H
#define C_MATH_DERIVNUMERICALALGORITHM_H

#define BACKWARD_DIFFERENCE 0
#define FORWARD_DIFFERENCE 1
#define CENTRAL_DIFFERENCE 2

#define SECOND_ORDER_ACCURACY 2
#define FOURTH_ORDER_ACCURACY 4
#define SIXTH_ORDER_ACCURACY 6
#define EIGHTH_ORDER_ACCURACY 8


double firstDerivative_1_arg(const char *expression, double x, double delta, int options);
/*
 * This function estimates a numerical derivative for a given one argument function at x
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * x            the point where derivative must be evaluated
 * delta        the dx for getting numerical derivative
 * options      which algorithm to use {0: BACKWARD_DIFFERENCE, 1: FORWARD_DIFFERENCE, 2: CENTRAL_DIFFERENCE}
 *
 */

double centralFirstDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * This function estimates a numerical derivative for a given one argument function at point x
 * with "central" finite difference method
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

double centralSecondDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6, 8}
 *
 * NOTE: it's good to use delta in range [1e-8, 1e-16] for this function
 * [double floating point accuracy IEEE 754-1985]
 * DX is defined DX = 1e-8 in _configurations.h
 */

double centralThirdDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * NOTE: it's good to use delta in range [1e-3, 1e-5] for this function
 * [double floating point accuracy IEEE 754-1985]
 * DX_SECOND is defined DX = 1e-4 in _configurations.h
 */

double centralFourthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-3, 1e-4] for this function
 * [double floating point accuracy IEEE 754-1985]
 * DX is defined DX = 1e-4 in _configurations.h
 */

double centralFifthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-1, 1e-3] for this function
 * [double floating point accuracy IEEE 754-1985]
 * DX_THIRD is defined DX = 1e-2 in _configurations.h
 */

double centralSixthDerivative_1_arg(const char *expression, double x, double delta, int accuracy);
/*
 * accuracy     defines the precision of algorithm, available accuracy order {2, 4, 6}
 *
 * NOTE: it's good to use delta in range [1e-1, 1e-2] for this function
 * [double floating point accuracy IEEE 754-1985]
 * DX_THIRD is defined DX = 1e-2 in _configurations.h
 */

#endif //C_MATH_DERIVNUMERICALALGORITHM_H
