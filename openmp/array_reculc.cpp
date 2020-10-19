#include <stdio.h>
#include <omp.h>
#include <vector>

//-fopenmp
int main() {
    int i;
    int N = 16000;
    std::vector<double> a, b;
    for (int i = 0; i < N; i++) {
        a.push_back(i);
        b.push_back(0);
    }
    double start;

    start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp for nowait
        for (i = 1; i < N - 1; i++) {
            b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3;
        }
#pragma omp sections
        {
#pragma omp section
            {
                printf("T%d: I'm first on first element!\n", omp_get_thread_num());
                b[0] = (a[0] + a[1]) / 2;
            }

#pragma omp section
            {
                printf("T%d: I'm first on last element!\n", omp_get_thread_num());
                b[N - 1] = (a[N - 1] + a[N - 2]) / 2;
            }

        }
    }
    printf("Time = %f\n", omp_get_wtime() - start);
    bool flag = true;
    for (int i = 1; i < N - 1; i++) {
        if (b[i] != i) {
            flag = false;
        }
    }
    printf("%s", flag ? "true" : "false");
}