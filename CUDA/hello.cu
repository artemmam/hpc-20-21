#include <stdio.h>


__global__ void mykernel(void) 
{
printf("Hello World from GPU!\n");
}


int main(void) 
{
mykernel<<<1,1>>>();
cudaDeviceSynchronize;
printf("Hello World from CPU!\n");

return 0;
}