#ifndef C_MATH_MONTECARLOINTEGRATIONALGORITHM_H
#define C_MATH_MONTECARLOINTEGRATIONALGORITHM_H

double monteCarloIntegration(const char *expression, double a, double b, unsigned int n, unsigned int options);

double monteCarloPointIntegration(const char *expression, double a, double b, unsigned int n);

double monteCarloRectangleIntegration(const char *expression, double a, double b, unsigned int n);

#endif //C_MATH_MONTECARLOINTEGRATIONALGORITHM_H
