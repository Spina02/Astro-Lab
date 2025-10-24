/* --------------------- bisection with var args ---------------------
* Adapt the ex. 06 to make it accept a variable number of arguments
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <float.h>

#define e 2.7182
#define eps 1.e-5

double f_parabolic(double x, va_list args) {
    double a  = va_arg(args, double);
    double b  = va_arg(args, double);
    double c  = va_arg(args, double);

    return a*x*x + b*x + c;
}

double f_trascendental_1(double x, va_list args) {
    return pow(x, x) - pow(e, -x) - 1;
}

double f_trascendental_2(double x, va_list args) {
    return 3*x - pow(e, x);
}

double f_cubic(double x, va_list args) {
    return x*x*x + x + 1;
}

// bisection solver
double bisection(double a, double b, double (*f)(double, va_list), ...) {

    va_list args;
    va_start(args, f);

    // compute the function values at the endpoints
    va_list args_a; 
    va_copy(args_a, args);
    double f_a = f(a, args_a);
    va_end(args_a);

    va_list args_b; 
    va_copy(args_b, args);
    double f_b = f(b, args_b);
    va_end(args_b);

    // check if f(a) and f(b) have opposite signs
    if (f_a * f_b > 0) {
        printf("f(a): %lf, f(b): %lf\n", f_a, f_b);
        printf("Error: f(a) and f(b) must be opposit in sign\n");
        return -FLT_MAX;
    }

    // compute the midpoint and its function value
    double c = (a + b) / 2.0;
    double f_c = f(c, args);
    
    // check if the midpoint is a root or the interval is small enough
    if (fabs(f_c) < eps || fabs(b - a) < eps)
        return c;

    // recursive call to the left or right half of the interval
    if (f_a * f_c < 0) 
        return bisection(a, c, f, args);
    else
        return bisection(c, b, f, args);
    va_end(args);
}

int main(int argc, char* argv[]) {

    double a, b, c1 = 0, c2 = 0, c3 = 0, res;

    if (argc != 4 && argc != 7) {
        printf("Error: invalid number of arguments\n\n");
        printf("Usage:\t %s <function> <a> <b>\nor \t %s parabolic <a> <b> <c1> <c2> <c3>\n", argv[0], argv[0]);
        printf("\nAvailable functions: parabolic, trascendental_1, trascendental_2, cubic\n");
        printf("<a> and <b> are the endpoints of the interval\n");
        printf("<c1> <c2> <c3> are the coefficients of the parabolic function\n");
        return 1;
    }
    
    char* function = argv[1];

    bool is_parabolic = !strcmp(function, "parabolic");

    if (argc == 4 && is_parabolic) {
        printf("You must specify parabolic coefficients");
        return 1;
    }

    a = atof(argv[2]);
    b = atof(argv[3]);

    if (is_parabolic) {
        c1 = atof(argv[4]);
        c2 = atof(argv[5]);
        c3 = atof(argv[6]);
    }

    double (*f)(double, va_list) = NULL;

    if (is_parabolic) {
        printf("using parabolic function: \t %.2lf*x^2 + %.2lf*x + %.2lf\n", c1, c2, c3);
        f = f_parabolic;
    } else if (!strcmp(function, "trascendental_1")) {
        printf("using trascendental_1 function: \t x^x - exp(-x) - 1\n");
        f = f_trascendental_1;
        printf("using trascendental_1 function:\t x^x - exp(-x) - 1\n");
    } else if (!strcmp(function, "trascendental_2")) {
        printf("using trascendental_2 function:\t 3*x - exp(x)\n");
        f = f_trascendental_2;
    } else if (!strcmp(function, "cubic")) {
        printf("using cubic function:\t\t x^3 + x + 1\n");
        f = f_cubic;
    } else {
        printf("Error: invalid function: %s\n", function);
        printf("Choose between: parabolic, trascendental_1, trascendental_2, cubic\n");
        return 1;
    }

    if (is_parabolic)
        res = bisection(a, b, f, c1, c2, c3);
    else
        res = bisection(a, b, f);

    if (res == -FLT_MAX) {
        return 1;
    }

    printf("result using bisection:\t\t %lf\n", res);

    return 0;
}