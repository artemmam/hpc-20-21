#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 1;
    int i;
    printf("'a' before parallel section =  %d\n",
           a);
    omp_set_num_threads(2);
    int N = 20;
    double start;

//    start = omp_get_wtime();
//#pragma omp parallel for schedule(guided)
//        for (i = 0; i < N; i++) {
//            a++;
//#pragma omp critical
//            printf("Incremented 'a' = %d by thread number %d\n",
//                   a, omp_get_thread_num());
//        }
//    printf("'a' after parallel section =  %d\n",
//           a);
//    printf("Time = %f",omp_get_wtime() - start);
#pragma omp parallel for collapse(2)
    for (i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a++;
#pragma omp critical
            printf("Incremented 'a' = %d by thread number %d\n",
                   a, omp_get_thread_num());
        }
    }
    printf("'a' after 2 parallel sections =  %d\n",
           a);
}

