/* ------------ Quadratic equation ------------
* Write a program which solves quadratic equations
* The coefficients must be asked to the user at runtime
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double* quadratic(float a, float b, float c) {
    double* res = (double*)malloc(2 * sizeof(double));

    double delta = b*b - 4*a*c;

    if (delta >= 0) {
        res[0] = (-b + sqrt(delta)) / (2*a);
        res[1] = (-b - sqrt(delta)) / (2*a);
        return res;
    } else {
        return NULL;
    }
}

int main() {
    
    double a, b, c;
    printf("insert the coefficients of the quadratic equation ax^2 + bx + c = 0\n[format 'a b c']: ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    double* res = quadratic(a, b, c);
    if (res == NULL) {
        printf("the quadratic equation has no real roots\n");
        return 0;
    }

    printf("the roots of the quadratic equation are %lf and %lf\n", res[0], res[1]);

    return 0;
}