#include <stdio.h>
#include <omp.h>
int main()
{
    omp_lock_t lock;
    omp_init_lock(&lock);
    int a = 0;
    int i;
    printf("'a' before parallel section =  %d\n",
           a);
    omp_set_num_threads(8);
    int N = 10000;
#pragma omp parallel for reduction(+:a)
    for (i = 0; i < N; i++) {
        //#pragma omp critical
        //#pragma omp atomic
        //omp_set_lock(&lock);
        a++;
        //omp_unset_lock(&lock);
    }

    printf("'a' after parallel section =  %d\n",
           a);
}