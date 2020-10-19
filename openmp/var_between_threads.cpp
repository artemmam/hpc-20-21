#include <stdio.h>
#include <omp.h>

int counter = 0;
#pragma omp threadprivate(counter)

int main()
{
    counter = 1;
#pragma omp parallel num_threads(8) //copyin(counter) // Allows threads to access the master thread's value
                                                     // , for a threadprivate variable.
    {
#pragma omp single copyprivate(counter)
    counter++;
        printf("Thread %d, %d\n",omp_get_thread_num(), counter);
    }
}