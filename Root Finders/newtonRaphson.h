#ifndef C_MATH_NEWTONRAPHSON_H
#define C_MATH_NEWTONRAPHSON_H

double newtonRaphson(const char *expression, double x0, double ete, double ere, double tol, int maxiter, int mode,
                     int *state);

#endif //C_MATH_NEWTONRAPHSON_H
