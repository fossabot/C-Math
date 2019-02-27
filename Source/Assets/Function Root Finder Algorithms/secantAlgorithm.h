#ifndef C_MATH_SECANTALGORITHM_H
#define C_MATH_SECANTALGORITHM_H

double secant(const char *expression, double x1, double x2, double ete, double ere, double tol, unsigned int maxiter,
              int mode, int *state);
/*
 * In numerical analysis, the secant method is a root-finding algorithm that uses a succession of roots
 * of secant lines to better approximate a root of a function f. The secant method can be thought of as
 * a finite-difference approximation of Newton's method. However, the method was developed independently
 * of Newton's method and predates it by over 3000 years
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
 */

#endif //C_MATH_SECANTALGORITHM_H
