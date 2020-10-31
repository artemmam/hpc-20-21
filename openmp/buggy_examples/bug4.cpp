#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 0;
    int i;
    printf("'a' before parallel section =  %d\n",
           a);
    omp_set_num_threads(8);
    int N = 20;
    double start;
#pragma omp parallel for
    for (i = 0; i < N; i++) {
#pragma omp parallel for
        for (int j = 0; j < N; j++) {
            a++;
            printf("Incremented 'a' = %d by thread number %d\n",
                   a, omp_get_thread_num());
        }
    }
    printf("'a' after 2 parallel sections =  %d\n",
           a);
}