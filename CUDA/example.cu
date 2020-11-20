#include <stdio.h>
#define N 10

__global__
void add(int *a, int *b) {
    int i = blockIdx.x;
	printf("Hello cuda from thread %d\n", i);
    b[i] = 2*a[i];
}

int main() {
    int ha[N], hb[N];
    int *da, *db;
    cudaMalloc((void **)&da, N*sizeof(int));
    cudaMalloc((void **)&db, N*sizeof(int));
    for (int i = 0; i<N; ++i) {
        ha[i] = i;
    }
    cudaMemcpy(da, ha, N*sizeof(int), cudaMemcpyHostToDevice);
    add<<<N, 1>>>(da, db);
    cudaMemcpy(hb, db, N*sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i<N; ++i) {
        printf("%d\n", hb[i]);
    }

    cudaFree(da);
    cudaFree(db);

    return 0;
}
