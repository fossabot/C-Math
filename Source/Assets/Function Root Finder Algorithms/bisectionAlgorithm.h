#ifndef C_MATH_BISECTIONALGORITHM_H
#define C_MATH_BISECTIONALGORITHM_H

double bisection(const char *expression, double a, double b, double ete, double ere, double tol, unsigned int maxiter,
                 int mode, int *state);
/*
 * The Bisection method in mathematics is a root-finding method that repeatedly bisects an interval and then selects
 * a sub-interval in which a root must lie for further processing. It is a very simple and robust method, but it is
 * also relatively slow. Because of this, it is often used to obtain a rough approximation to a solution which is
 * then used as a starting point for more rapidly converging methods. The method is also called the interval
 * halving method, the binary search method, or the dichotomy method.
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a            starting point of interval [a, b]
 * b            ending point of interval [a, b]
 * ete          estimated true error
 * ere          estimated relative error
 * tol          tolerance error
 * maxiter      maximum iteration threshold
 * mode         show process {0: no, 1: yes}
 * state        is answer found or not, will set value of state to 0 if no answers been found
 *
 *
 */

#endif //C_MATH_BISECTIONALGORITHM_H
