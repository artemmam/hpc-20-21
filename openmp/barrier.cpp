#include <stdio.h>
#include <omp.h>
int main()
{
    int np = omp_get_num_procs();
    printf("Total number of processors is %d\n", np);
    omp_set_num_threads(4);

#pragma omp parallel
    {

    printf("Hello, World from thread %d of %d\n",
           omp_get_thread_num(), omp_get_num_threads());
//#pragma omp barrier

        printf("Goodbuy from thread %d of %d\n",
               omp_get_thread_num(), omp_get_num_threads());
    }
}