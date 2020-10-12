#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 1;
    printf("'a' before parallel section =  %d\n",
           a);
    omp_set_num_threads(2);
#pragma omp parallel private(a)
    {
        a++;
        printf("Incremented 'a' %d by thread number %d\n",
               a, omp_get_thread_num());
    }
    printf("'a' after parallel section =  %d\n",
           a);
    }