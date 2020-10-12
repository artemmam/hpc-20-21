#include <stdio.h>
#include <omp.h>
int main()
{
    int np = omp_get_num_procs();
    int nt = omp_get_num_threads();
    printf("Total number of processors is %d\n", np);
    printf("Total number of processors doing this part is %d\n", nt);
    omp_set_num_threads(np);
    //omp_set_dynamic(1);

#pragma omp single
    printf("Hello, World from thread %d of %d\n",
           omp_get_thread_num(), omp_get_num_threads());
}