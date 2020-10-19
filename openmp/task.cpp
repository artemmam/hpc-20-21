#include <stdio.h>
#include <omp.h>
int fib(int n)
{
    int i, j;
    #pragma omp critical
        printf("Thread number %d put task for n =  %d\n", omp_get_thread_num(), n);
    if (n<2)
    {
        return n;
    }
    else
    {
#pragma omp task shared(i) firstprivate(n)
#pragma omp critical
        printf("Thread number %d take task i for n =  %d\n", omp_get_thread_num(), n);
        i=fib(n-1);

#pragma omp task shared(j) firstprivate(n)
#pragma omp critical
        printf("Thread number %d take task j for n =  %d\n", omp_get_thread_num(), n);
        j=fib(n-2);

#pragma omp taskwait
        return i+j;
    }
}

int main()
{
    int n = 4;
    omp_set_num_threads(8);

#pragma omp parallel shared(n)
    {
#pragma omp single
        printf ("fib(%d) = %d\n", n, fib(n));
    }
}
