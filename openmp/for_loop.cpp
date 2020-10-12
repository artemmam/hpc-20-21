#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 1;
    int i;
    printf("'a' before parallel section =  %d\n",
           a);
    omp_set_num_threads(2);
    int N = 10;
#pragma omp parallel for
        for (i = 0; i < N; i++) {
            a++;
            printf("Incremented 'a' = %d by thread number %d\n",
                   a, omp_get_thread_num());
        }

    printf("'a' after parallel section =  %d\n",
           a);
}

