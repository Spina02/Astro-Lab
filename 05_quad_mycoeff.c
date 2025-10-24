/* --------------------- quadratic with pointers ---------------------
* Adapt ex. 01 to use pointers to the coefficients.
* The program should ask the user for the coefficients and print the roots.
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
        printf("the quadratic equation has no real roots\n");
        return NULL;
    }
}

void myCoeff(double* a, double* b, double* c) {
    // *a = 1;
    // *b = 2;
    // *c = 1;

    printf("insert the coefficients of the quadratic equation ax^2 + bx + c = 0\n[format 'a b c']: ");
    scanf("%lf %lf %lf", a, b, c);
}

int main() {
    
    double a, b, c;

    myCoeff(&a, &b, &c);

    double* res = quadratic(a, b, c);
    if (res == NULL) {
        return 0;
    }

    printf("the roots of the quadratic equation are %lf and %lf\n", res[0], res[1]);

    return 0;
}
