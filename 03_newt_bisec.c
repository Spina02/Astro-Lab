/* --------------- newton vs bisection ---------------
* Write a program that implements the newton or bisection method to find the root of a function.
* The program should take the function, the interval and the initial guess as arguments.
* 
* Implement also a test function with a well known root
* The funciton used must be set using env. variables at cpompiling time
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define e 2.7182
#define eps 1.e-5

// test function (well known root: x = 1)
#ifdef TEST
    #define DESCRIPTION "x^2 - 1 = 0"
    // f = x^2 - 1 = 0
    // f' = 2x

    double f(double x) {
        return x*x - 1;
    }

    double f_prime(double x) {
        return 2*x;
    }
#else
    #define DESCRIPTION "x^x - exp(-x) - 1 = 0"
    // f = x^x - exp(-x) - 1 = 0
    // f' = x^x * (ln(x) + 1) + exp(-x)

    double f(double x) {
        return pow(x, x) - pow(e, -x) - 1;
    }

    double f_prime(double x) {
        return pow(x, x) * (1 + log(x)) + pow(e, -x);
    }
#endif

#ifdef NEWTON

    #define METHOD "newton"

    // newton solver
    double newton(double x0) {
        // x_{n+1} = x_n - f(x_n) / f'(x_n)
        double x_next = x0 - f(x0)/f_prime(x0);

        // check if the newton step is small enough
        if (fabs(x0 - x_next) < eps) 
            return x_next;
        else
            // recursive call to the next step
            return newton(x_next);
    }

    // wrapper that takes 3 args for comparibility
    double solve(double a, double b, double x0) {
        return newton(x0);
    }

#else

    #define METHOD "bisection"

    // bisection solver
    double bisection(double a, double b) {

        // compute the function values at the endpoints
        double f_a = f(a);
        double f_b = f(b);

        // check if f(a) and f(b) have opposite signs
        if (f_a * f_b > 0) {
            printf("Error: f(a) and f(b) must be opposit in sign\n");
            return -1;
        }

        // compute the midpoint and its function value
        double c = (a + b) / 2.0;
        double f_c = f(c);

        // check if the midpoint is a root or the interval is small enough
        if (fabs(f_c) < eps || fabs(b - a) < eps)
            return c;
        
        // recursive call to the left or right half of the interval
        if (f_a * f_c < 0) {
            return bisection(a, c);
        } else {
            return bisection(c, b);
        }
    }

    // wrapper that takes 3 args for comparibility
    double solve(double a, double b, double x0) {
        return bisection(a, b);
    }

#endif

int main() {
    double x0 = 0.5;
    double res = solve(-2, 2, x0);
    printf("method used: \t\t%s\n", METHOD);
    printf("equation used: \t\t%s\n", DESCRIPTION);
    printf("interval: \t\t[%d, %d]\n", -2, 2);
    printf("initial guess: \t\t%.2g\n", 0.5);
    printf("result: \t\t%lf\n", res);
}