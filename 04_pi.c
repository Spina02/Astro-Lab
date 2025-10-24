/* --------------- pi estimation ---------------
* Write a program that estimates the value of pi.
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double estimate_pi(int N_iter) {

    /* Let's consider a circle of radius r into a square of side l=2*r: 
    *       r = l/2
    *       A_s = l^2
    *       A_c = pi * r^2
    *           = pi * l^2 / 4 
    *           = pi * A_s / 4
    *            
    *       pi = 4 * A_c / A_s
    *
    *   we approximate A_c with count_circ and A_q with N_iter
    */
    
    unsigned int count_circ = 0;

    for (int i = 0; i < N_iter; i++) {
        // random point coords in [-1, 1]
        double rand_x = (2.0 * rand() / RAND_MAX) - 1.;
        double rand_y = (2.0 * rand() / RAND_MAX) - 1.;

        // if the random point is inside the unit circle, increment counter
        // avoid sqrt to speed up the computation (useless for unit circle)
        if (rand_x*rand_x + rand_y*rand_y <= 1) count_circ++;
    }

    return count_circ*4. / (double) N_iter;
}

int main() {
    printf("estimating pi with 10^1 iterations:\t");
    fflush(stdout);
    printf("%lf\n", estimate_pi(10));           // 3.200000
    printf("estimating pi with 10^3 iterations: \t");
    fflush(stdout);
    printf("%lf\n", estimate_pi(1000));         // 3.080000
    printf("estimating pi with 10^6 iterations: \t");
    fflush(stdout);
    printf("%lf\n", estimate_pi(1000000));      // 3.143000
    printf("estimating pi with 10^9 iterations: \t");
    fflush(stdout);
    printf("%lf\n", estimate_pi(1000000000));   // 3.141575
}

