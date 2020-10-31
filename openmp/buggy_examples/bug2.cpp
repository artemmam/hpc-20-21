#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000

int main (int argc, char *argv[])
{
    int nthreads, tid, i;
    float a[N], b[N];
    omp_lock_t locka, lockb;

/* Initialize the locks */
    omp_init_lock(&locka);
    omp_init_lock(&lockb);

/* Initialize the arrays */
    for (i=0; i<N; i++) {
        a[i]=0;
        b[i]=0;
    }

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel shared(a, b, nthreads, locka, lockb) private(tid, i)
    {

        /* Obtain thread number and number of threads */
        tid = omp_get_thread_num();
#pragma omp master
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
        printf("Thread %d starting...\n", tid);
#pragma omp barrier

#pragma omp sections nowait
        {
#pragma omp section
            {
                omp_set_lock(&locka);
                printf("Thread %d updating a[]\n",tid);
                for (i=0; i<N; i++)
                    a[i] += i;
                omp_set_lock(&lockb);
                printf("Thread %d updating b[]\n",tid);
                for (i=0; i<N; i++)
                    b[i] += i;
                omp_unset_lock(&lockb);
                omp_unset_lock(&locka);
            }

#pragma omp section
            {
                omp_set_lock(&lockb);
                printf("Thread %d updating b[]\n",tid);
                for (i=0; i<N; i++)
                    b[i] += 2 * i;
                omp_set_lock(&locka);
                printf("Thread %d adding b[] to a[]\n",tid);
                for (i=0; i<N; i++)
                    a[i] += b[i] + i;
                omp_unset_lock(&locka);
                omp_unset_lock(&lockb);
            }

        }  /* end of sections */
    }  /* end of parallel region */

}
