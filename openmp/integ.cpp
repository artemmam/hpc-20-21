#include <stdio.h>
#include <omp.h>

const double a = 0;
const double b = 1;
const int n = 100000000;
const double h=(b - a) / n;


double f(double x) {
    return 4. / (1. + x * x);
}

int main() {
    double S = 0.0;
    double start;

    start = omp_get_wtime();
    for(int i = 0; i < n; i ++) {
        S+=f(a+i*h + 0.5 * h);
    }
    printf("Integ consistently = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);

    S = 0.0;
    start = omp_get_wtime();
#pragma omp parallel for
    for(int i = 0; i < n; i ++) {
#pragma omp critical
        S+=f(a+i*h + 0.5 * h);
    }
    printf("Integ critical = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);

    S = 0.0;
    start = omp_get_wtime();
#pragma omp parallel for
    for(int i = 0; i < n; i ++) {
#pragma omp atomic
        S+=f(a+i*h + 0.5 * h);
    }
    printf("Integ atomic = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);

    start = omp_get_wtime();
    S = 0.0;
#pragma omp parallel
    {
        double S_tmp = 0;
#pragma omp for
    for(int i = 0; i < n; i ++) {
        S_tmp += f(a + i * h + 0.5 * h);
    }
#pragma omp atomic
        S+=S_tmp;
    }
    printf("Integ with tmp atomic = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);

    start = omp_get_wtime();
    S = 0.0;
#pragma omp parallel
    {
        double S_tmp = 0;
#pragma omp for
        for(int i = 0; i < n; i ++) {
            S_tmp += f(a + i * h + 0.5 * h);
        }
#pragma omp critical
        S+=S_tmp;
    }
    printf("Integ with tmp critical = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);


S = 0;
    int num_threads = omp_get_max_threads();
    double sum_tmp[num_threads];
    start = omp_get_wtime();
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        sum_tmp[id] = 0;
#pragma omp for nowait
        for (int i = 0; i < n; i++) {
            double S_loc = 0;
            S_loc=f(a+i*h + 0.5 * h);
            sum_tmp[id] += S_loc;
        }
#pragma omp atomic
        S += sum_tmp[id];

    }
    printf("Integ with array = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);

    S = 0;
    int pad = 8;
    double sum_tmp_padded[num_threads*pad];
    start = omp_get_wtime();
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int pos = id*pad;
        sum_tmp_padded[pos] = 0;
#pragma omp for nowait
        for (int i = 0; i < n; i++) {
            double S_loc = 0;
            S_loc=f(a+i*h + 0.5 * h);
            sum_tmp_padded[pos] += S_loc;
        }
#pragma omp atomic
        S += sum_tmp_padded[pos];

    }
    printf("Integ with padded array = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);


    S = 0;
    start = omp_get_wtime();
#pragma omp parallel for reduction(+:S)
    for(int i = 0; i < n; i ++) {
        S+=f(a+i*h + 0.5 * h);
    }
    printf("Integ with reduction = %.16f\n", S*h);
    printf("Time = %f\n", omp_get_wtime() - start);
}
