#ifndef C_MATH_GRADIENTASCENTALGORITHM_H
#define C_MATH_GRADIENTASCENTALGORITHM_H

double gradientAscent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                      int mode, int *state);

double gradientAscentInterval(const char *expression, double a, double b, double ete, double ere, double gamma,
                              unsigned int maxiter, int mode);

#endif //C_MATH_GRADIENTASCENTALGORITHM_H
