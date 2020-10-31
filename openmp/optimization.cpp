#include <stdio.h>
#include <omp.h>
#include "vector"
#include <cmath>
#include <algorithm>
#include <iostream>

double f(double x1, double x2){
    return pow((x1 - 1), 2) + pow((x2 - 2.5), 2);
}
int main()
{
    omp_set_num_threads(8);
std::vector<double> X1, X2;
int N = 10000;
double a = 0;
double b = 10;
    for (int i = 0; i < N; i++) {
        X1.push_back(a + i*((b - a)/(N)));
        X2.push_back(a + i*((b - a)/(N)));
    }
    double global_min = 100, x1_min, x2_min  = 0;
    double start = omp_get_wtime();
#pragma omp parallel
    {
        double min_f = 100;
        double x1_min_loc, x2_min_loc = 0;
#pragma omp for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (f(X1[i], X2[j]) < min_f) {
                    min_f = f(X1[i], X2[j]);
                    x1_min_loc = X1[i];
                    x2_min_loc = X2[j];
                }
            }
        }
#pragma omp critical
        {
            if (min_f < global_min) {
                global_min = min_f;
                x1_min = x1_min_loc;
                x2_min = x2_min_loc;
            }
        }
    }
    printf("Min value = %f\n", global_min);
    printf("x1 = %f, x2 = %f\n", x1_min, x2_min);
    printf("Time = %f", omp_get_wtime() - start);
}

