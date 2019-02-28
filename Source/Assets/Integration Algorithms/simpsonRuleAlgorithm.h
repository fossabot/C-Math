#ifndef C_MATH_SIMPSONRULEALGORITHM_H
#define C_MATH_SIMPSONRULEALGORITHM_H

double simpsonRule(const char *expression, double a, double b, unsigned int n, int options, int verbose);
/*
 * In numerical analysis, Simpson's rule is a method for numerical integration,
 * the numerical approximation of definite integrals. Specifically, it is
 * the following approximation for n equally spaced subdivisions
 *
 * ARGUMENTS:
 * expressions   the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use, better to be an even number
 * options       which point of sub-interval to use  {0: 1/3 rule, 1: 3/8 rule}
 * verbose       show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_SIMPSONRULEALGORITHM_H
