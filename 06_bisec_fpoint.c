/* --------------------- bisection with function pointer ---------------------
* Adapt ex. 03 to use the bisection method to find the root of a function.
* This time, the function should be passed as a function pointer.
*
* The program should take the function, the interval and the coefficients of the function as arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define e 2.7182
#define eps 1.e-5

double f_parabolic(double x, double a, double b, double c) {
    return a*x*x + b*x + c;
}

double f_trascendental_1(double x, double a, double b, double c) {
    return pow(x, x) - pow(e, -x) - 1;
}

double f_trascendental_2(double x, double a, double b, double c) {
    return 3*x - pow(e, x);
}

double f_cubic(double x, double a, double b, double c) {
    return x*x*x + x + 1;
}

// bisection solver
double bisection(double a, double b,double c1, double c2, double c3, double (*f)(double, double, double, double)) {

    // compute the function values at the endpoints
    double f_a = f(a, c1, c2, c3);
    double f_b = f(b, c1, c2, c3);

    // check if f(a) and f(b) have opposite signs
    if (f_a * f_b > 0) {
        printf("f(a): %lf, f(b): %lf\n", f_a, f_b);
        printf("Error: f(a) and f(b) must be opposit in sign\n");
        return -FLT_MAX;
    }

    // compute the midpoint and its function value
    double c = (a + b) / 2.0;
    double f_c = f(c, c1, c2, c3);

    // check if the midpoint is a root or the interval is small enough
    if (fabs(f_c) < eps || fabs(b - a) < eps)
        return c;
    
    // recursive call to the left or right half of the interval
    if (f_a * f_c < 0) {
        return bisection(a, c, c1, c2, c3, f);
    } else {
        return bisection(c, b, c1, c2, c3, f);
    }
}

int main(int argc, char* argv[]) {

    if (argc != 7) {
        printf("Error: invalid number of arguments\n");
        printf("Usage: %s <function> <a> <b> <c1> <c2> <c3>\n", argv[0]);
        printf("Available functions: parabolic, trascendental_1, trascendental_2, cubic\n");
        return 1;
    }

    char* function = argv[1];
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    double c1 = atof(argv[4]);
    double c2 = atof(argv[5]);
    double c3 = atof(argv[6]);

    double (*f)(double, double, double, double) = NULL;

    if (!strcmp(function, "parabolic")) {
        printf("using parabolic function:\t %lf*x^2 + %lf*x + %lf\n", c1, c2, c3);
        f = f_parabolic;
    } else if (!strcmp(function, "trascendental_1")) {
        printf("using trascendental_1 function:\t x^x - exp(-x) - 1\n");
        f = f_trascendental_1;
    } else if (!strcmp(function, "trascendental_2")) {
        printf("using trascendental_2 function:\t 3*x - exp(x)\n");
        f = f_trascendental_2;
    } else if (!strcmp(function, "cubic")) {
        printf("using cubic function:\t x^3 + x + 1\n");
        f = f_cubic;
    } else {
        printf("Error: invalid function: %s\n", function);
        printf("Choose between: parabolic, trascendental_1, trascendental_2, cubic\n");
        return 1;
    }

    double res = bisection(a, b, c1, c2, c3, f);
    if (res == -FLT_MAX) {
        return 1;
    }
    printf("result using bisection: \t %lf\n", res);
}