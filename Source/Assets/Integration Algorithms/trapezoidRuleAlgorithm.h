#ifndef C_MATH_TRAPEZOIDRULEALGORITHM_H
#define C_MATH_TRAPEZOIDRULEALGORITHM_H

double trapezoidRule(const char *expression, double a, double b, unsigned int n, double previous, int verbose);
/*
 * In mathematics, and more specifically in numerical analysis, the trapezoidal rule
 * (also known as the trapezoid rule or trapezium rule) is a technique for approximating the definite integral.
 *
 * ARGUMENTS:
 * expressions   the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 * previous      use previous integral in calculation
 * verbose       show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_TRAPEZOIDRULEALGORITHM_H
