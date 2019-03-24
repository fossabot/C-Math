#ifndef C_MATH_ROMBERGALGORITHM_H
#define C_MATH_ROMBERGALGORITHM_H

double romberg(const char *expression, double a, double b, unsigned int k, double tol, int verbose);
/*
 * In numerical analysis, Romberg's method is used to estimate the definite integral
 * by applying Richardson extrapolation repeatedly on the trapezium rule or
 * the rectangle rule. The estimates generate a triangular array. Romberg's method is
 * a Newton–Cotes formula – it evaluates the integrand at equally spaced points.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * k             degree of integration
 * tol           tolerance error
 * verbose       show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_ROMBERGALGORITHM_H
