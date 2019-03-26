#ifndef C_MATH_GOLDENSECTIONOPTALGORITHM_H
#define C_MATH_GOLDENSECTIONOPTALGORITHM_H

double goldenSectionOptimization(const char *expression, double a, double b, double tol, unsigned int maxiter,
                                 int maximum, int verbose);
/*
 * The golden-section search is a technique for finding the extremum (minimum or maximum) of a strictly unimodal
 * function by successively narrowing the range of values inside which the extremum is known to exist.
 * The technique derives its name from the fact that the algorithm maintains the function values for triples of
 * points whose distances form a golden ratio. The algorithm is the limit of Fibonacci search (also described
 * below) for a large number of function evaluations. Fibonacci search and golden-section search were discovered
 * by Kiefer (1953) (see also Avriel and Wilde (1966)).
 *
 * ARGUMENTS:
 * expressions  the function expression, it must be a string array like "x^2+1"
 * a            starting point of interval [a, b]
 * b            ending point of interval [a, b]
 * tol          error threshold
 * maxiter      maximum iteration threshold
 * maximum      this option will let user to find maximum instead of minimum {0: no, 1: yes}
 * verbose      show process {0: no, 1: yes}
 *
 */

#endif //C_MATH_GOLDENSECTIONOPTALGORITHM_H
