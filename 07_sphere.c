/*  Exercise 7: Sphere
* 
*  Write a program that generates N random points in a circle of radius r1 
*  and M random points in a circle of radius r2.
*
*  The points should be saved in a file named sphere%05d_%05.5f.txt, where
*  %05d is the number of the points and %05.5f is the radius of the circle.
*
*  The program should take the number of points N, M and the radius r1, r2 as arguments.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>

typedef struct {
    double x;
    double y;
} point;

point* populate_sphere(point* sphere, int N, double r) {

    int count = 0;

    while (count < N) {

        double x = r*((2.0 * rand() / RAND_MAX) - 1.);
        double y = r*((2.0 * rand() / RAND_MAX) - 1.);

        if (sqrt(x*x + y*y) <= r) {
            sphere[count].x = x;
            sphere[count].y = y;
            count++;
        }
    }

    return sphere;
}

void save_sphere(point* sphere, int N, double r) {
    char filename[100];
    // create artifacts directory if it doesn't exist
    mkdir("artifacts", 0755);
    sprintf(filename, "artifacts/sphere%05d_%05.5f.txt", N, r);
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < N; i++) {
        fprintf(f, "%lf %lf\n", sphere[i].x, sphere[i].y);
    }
    fclose(f);
    printf("Sphere saved in %s\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s N M r1 r2\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    double r1 = atof(argv[3]);
    double r2 = atof(argv[4]);
    
    if (N <= 0 || N > 99999 || M <= 0 || M > 99999) {
        printf("Error: N and M must be between 1 and 99999\n");
        return 1;
    }

    if (r1 <= 0 || r1 > 99999 || r2 <= 0 || r2 > 99999) {
        printf("Error: r1 and r2 must be between 0 and 99999\n");
        return 1;
    }

    // we haven't seen malloc yet, so we'll use a fixed size array
    point sphere1[N];
    point sphere2[M];

    populate_sphere(sphere1, N, r1);
    populate_sphere(sphere2, M, r2);

    save_sphere(sphere1, N, r1);
    save_sphere(sphere2, M, r2);

    return 0;
}