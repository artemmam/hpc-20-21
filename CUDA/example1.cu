#include <iostream> 
#define BLOCK_SIZE 16
#define GRID_SIZE 1


__global__ void test(int *A, int *B,int *C)
{

    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;

    //if (i < BLOCK_SIZE && j < BLOCK_SIZE)
        C[i][j] = A[i][j] + B[i][j];

}

int main()
{
	
	
	
    int* d_A;
    int* d_B;
    int* d_C;
	int A[BLOCK_SIZE][BLOCK_SIZE];
	int B[BLOCK_SIZE][BLOCK_SIZE];
    int C[BLOCK_SIZE][BLOCK_SIZE];

    for(int i=0;i<BLOCK_SIZE;i++)
      for(int j=0;j<BLOCK_SIZE;j++)
      {
        A[i][j]=i+j;
        B[i][j]=i+j;
      }
	cudaMalloc((void **)&d_A, sizeof A);
	cudaMalloc((void **)&d_B, sizeof B);
	cudaMalloc((void **)&d_C, sizeof C);
	cudaMemcpy(d_A, A,sizeof A, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, B,sizeof B, cudaMemcpyHostToDevice);
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE); 
    dim3 dimGrid(GRID_SIZE, GRID_SIZE); 

    test<<<dimGrid, dimBlock>>>(d_A,d_B,d_C); 

    cudaMemcpy(C,d_C,sizeof C , cudaMemcpyDeviceToHost);

    for(int i=0;i<BLOCK_SIZE;i++)
      for(int j=0;j<BLOCK_SIZE;j++)
      {
        printf("%d\n",C[i][j]);

      }
}