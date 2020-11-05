#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 20
#define K 6

int get_neighb(int* data, int cor, int p){
    int ret = 0;
    if (cor - 1 >= 0)
        ret += data[cor - 1];
    if (cor + 1 < N*(N/p+2))
        ret += data[cor + 1];
    if (cor - N >= 0)
        ret += data[cor - N];
    if (cor + N < N*(N/p+2))
        ret += data[cor + N];
    if (cor - N - 1 >= 0)
        ret += data[cor - N - 1];
    if (cor + N - 1 < N*(N/p+2))
        ret += data[cor + N - 1];
    if (cor - N + 1 >= 0)
        ret += data[cor - N + 1];
    if (cor + N + 1 < N*(N/p+2))
        ret += data[cor + N + 1];
    return ret;
}

int main(int argc, char* argv[])
{
    int r = 0;
    int p = 1;
    int* data;
    int* new_data;
    int l_rank = 0,r_rank = 0;
    srand(14);
    MPI_Status st;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    data = new int[N*(N/p + 2)];
    new_data = new int[N*(N/p)];
    if(r == 0){
        l_rank = p - 1;
        r_rank = r + 1;
    } else if (r == p - 1){
        r_rank = 0;
        l_rank = r - 1;
    } else {
        r_rank = r + 1;
        l_rank = r - 1;
    }
    for(int k = 0; k < K;k++) {
        for (int i = N; i < N * (N / p + 1); i++) {
            if (k == 0) {
                int ran = rand();
                if (ran % 3 == 0) {
                    new_data[i - N] = 1;
                } else
                    new_data[i - N] = 0;
            } else {
                int neigb = get_neighb(data,i,p);
                if(neigb < 2 or neigb > 3)
                    new_data[i - N] = 0;
                else if (neigb == 3)
                    new_data[i - N] = 1;
                else
                    new_data[i - N] = data[i];
            }
        }
        for (int j = 0; j < N * (N / p); j++) {
            data[j + N] = new_data[j];
        }
        MPI_Request req[4];
        MPI_Status stat[4];
        MPI_Isend(&data[N],N,MPI_INT,r_rank,1,MPI_COMM_WORLD,&req[0]);
        MPI_Isend(&data[N * (N/p)],N,MPI_INT,l_rank,1,MPI_COMM_WORLD,&req[1]);
        MPI_Irecv(data,N,MPI_INT,l_rank,1,MPI_COMM_WORLD,&req[2]);
        MPI_Irecv(&data[N * (N/p + 1)],N,MPI_INT,r_rank,1,MPI_COMM_WORLD,&req[3]);
        MPI_Waitall(4,req,stat);
    }
    int* full_field = new int[N*N];
    for(int i = 0; i < N*(N/p); i++)
        full_field[i] = data[i + N];
    MPI_Gather(&data[N],N*(N/p),MPI_INT,&full_field[N*(N/p)],N*(N/p),MPI_INT,0,MPI_COMM_WORLD);
    if(r == 0)
        for(int i = 0; i < N*N;i++){
            printf("%d ",full_field[i]);
            if ((i + 1) % N == 0)
                printf("\n");
        }
    MPI_Finalize();
}