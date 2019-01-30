#ifndef C_MATH_GRADIENTDESCENTALGORITHM_H
#define C_MATH_GRADIENTDESCENTALGORITHM_H

double gradientDescent(const char *expression, double x0, double ete, double ere, double gamma, unsigned int maxiter,
                       int mode, int *state);

#endif //C_MATH_GRADIENTDESCENTALGORITHM_H
