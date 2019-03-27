#ifndef C_MATH_SIMPLEMAXMINFINDERALGORITHM_H
#define C_MATH_SIMPLEMAXMINFINDERALGORITHM_H

double *simpleMaxMinFinder(const char *expression, double a, double b, unsigned int n);
/*
 * this function will find global maximum and minimum of a function in interval [a, b]
 * through sampling y = f(x) and comparing it with previous values
 *
 * ARGUMENTS:
 * expressions   the function expression, it must be a string array like "x^2+1"
 * a             starting point of interval [a, b]
 * b             ending point of interval [a, b]
 * n             number of sub-intervals to use
 *
 * RETURN:       a pointer to a double array of size 2
 *               this array contains x where maximum
 *               and minimum of function occurs
 *               result[0] = maximum
 *               result[1] = minimum
 *
 */

#endif //C_MATH_SIMPLEMAXMINFINDERALGORITHM_H
