#ifndef C_MATH_MONTECARLOINTEGRATIONALGORITHM_H
#define C_MATH_MONTECARLOINTEGRATIONALGORITHM_H

double monteCarloIntegration(const char *expression, double a, double b, unsigned int n, unsigned int options,
                             int verbose);

/*
 * In mathematics, Monte Carlo integration is a technique for numerical integration using random numbers.
 * It is a particular Monte Carlo method that numerically computes a definite integral. While other algorithms
 * usually evaluate the integrand at a regular grid, Monte Carlo randomly choose points at which
 * the integrand is evaluated. This method is particularly useful for higher-dimensional integrals.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 * options       type of monte carlo to be used {0: random points ,  1: random rectangles}
 * verbose       show process {0: no, 1: yes}
 *
 */

double monteCarloPointIntegration(const char *expression, double a, double b, unsigned int n, int verbose);

/*
 * In this method we use random points and then calculate the area under function based on
 * proportional relation between points under the curve of function and all points to the area
 * of rectangle which surrounds whole function curve
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 * verbose       show process {0: no, 1: yes}
 *
 */

double monteCarloRectangleIntegration(const char *expression, double a, double b, unsigned int n, int verbose);
/*
 * In this method we use the same approach as riemann sum rule
 * but the difference is we use random rectangles
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 * verbose       show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_MONTECARLOINTEGRATIONALGORITHM_H
