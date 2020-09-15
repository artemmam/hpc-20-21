#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>


pthread_mutex_t mut;
static int N, nrow;
int **A, **B, **C;
double t;
int num_threads;

void setup_matrices ()
{
    int i, j;
    A = new int*[N];
    B = new int*[N];
    C = new int*[N];
    for(i = 0; i < N; ++i)
    {
        A[i] = new int[N];
        B[i] = new int[N];
        C[i] = new int[N];
    }
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            A[i][j] = 1;
            B[i][j] = 2;
            C[i][j] = 0;
        }
    }
}

void show_matrices (int **A) {
    int i, j;
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}
void * worker (void *arg)
{
    int i;
    while (1)
    {
        int oldrow;
        pthread_mutex_lock (&mut);
        if(nrow >= N)
        {
            pthread_mutex_unlock (&mut);
            break;
        }
        oldrow = nrow;
        nrow++;
        pthread_mutex_unlock (&mut);
        for (i = 0; i < N; i++)
        {
            int j;
            double t = 0.0;
            for (j = 0; j < N; j++)
                t += A[oldrow][j] * B[j][i];
            C[oldrow][i] = t;
        }
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    int i;
    pthread_mutex_init(&mut, NULL);
    num_threads = atoi (argv[1]);
    pthread_t th_arr[num_threads];
    N = atoi (argv[2]);
    t = time(NULL);
    printf("Matrix size %d\n", N);
    printf("Number of threads: %d\n", num_threads);
    setup_matrices ();
    for (i = 0; i < num_threads; i++)
        pthread_create (&th_arr[i], NULL, worker, NULL);
    for (i = 0; i < num_threads; i++)
        pthread_join (th_arr[i], NULL);
//    show_matrices(A);
//    show_matrices(B);
//    show_matrices(C);
    pthread_mutex_destroy(&mut);
}

