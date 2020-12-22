#include <math.h>
#include <vector>
#include <omp.h>
#include <stdio.h>
#include <iostream>


int main() {
    int NUM_THREADS = 8;
    int N = 1000000;
    double sum = 0, sum_local[NUM_THREADS], x[N], y[N];

    //std::vector<double> x, y;
    for (int i = 0; i < N; i++) {
        x[i] = 0.001;
        y[i] = 0.02 * i;
    }
#pragma omp parallel num_threads(NUM_THREADS)
    {
        int me = omp_get_thread_num();
        sum_local[me] = 0.0;
#pragma omp for
        for (int i = 0; i < N; i++)
            sum_local[me] += x[i] * y[i];

#pragma omp atomic
        sum += sum_local[me];
    }
    printf("%f", sum);
}
