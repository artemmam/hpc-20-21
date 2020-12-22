#include <math.h>
#include <vector>
#include <omp.h>
#include <stdio.h>
#include <iostream>


int main() {
    int i;
    int n = 10;
    int m = 10;
    std::vector<int> a, b, y, z;
    for (int i = 0; i < m; i++) {
        a.push_back(i);
        b.push_back(0);
        z.push_back(i);
        y.push_back(0);
    }
#pragma omp parallel
    {
#pragma omp for
        for (i = 1; i < n; i++) {
            printf("Thread number %d first cycle\n",
                   omp_get_thread_num());
            b[i] = int((a[i] + a[i - 1]) / 2.0);
        }
#pragma omp for
        for (i = 0; i < m; i++) {
            y[i] = int(sqrt(z[i]));
            printf("Thread number %d second cycle\n",
                   omp_get_thread_num());
        }
    }
    for (int i = 0; i < m; i++) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < m; i++) {
        std::cout << y[i] << " ";
    }
}

