/* ----------- Factorial -----------
* Write a program that calculates the factorial of a number.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long factorial(long n) {
    if (n == 0) return 1;
    return n * factorial(n-1);
}

int main() {

    long n;
    printf("Insert a number to calculate its factorial: ");
    scanf("%ld", &n);
    printf("the factorial of %ld is %ld\n", n, factorial(n));
    
    return 0;
}

// When occurs overflow:
// int       -> 13
// long      -> 20
// long long -> 20 (at least on my machine)
