#include <stdio.h>
#include <omp.h>


int main()
{
#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("T%d: foo\n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("T%d: bar\n", omp_get_thread_num());
        }
    }// omp sections
}

