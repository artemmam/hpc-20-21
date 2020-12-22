# include <mpi.h>
# include <stdio.h>
# include <string.h>
#include <stdlib.h>

float compute_avg(float *array, int num_elements) {
    float sum = 0;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
        //printf("%f \n", array[i]);
    }
    //printf("%f", sum / num_elements);
    return sum / num_elements;
}


int main(int argc, char *argv[]) {

    int elements_per_proc = 25;
    int arr_size = elements_per_proc * 4;


    MPI_Init(&argc, &argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    float rand_nums[arr_size];


    if (world_rank == 0) {
        for (int i = 0; i < arr_size; ++i) {
            rand_nums[i] = i;
        }
    }

// Create a buffer that will hold a subset of the random numbers
    float sub_rand_nums[elements_per_proc]; //= malloc(sizeof(float) * elements_per_proc);
//float *sub_rand_nums = (float *)malloc(sizeof(float) * elements_per_proc);

// Scatter the random numbers to all processes
    MPI_Scatter(rand_nums, elements_per_proc, MPI_FLOAT, sub_rand_nums,
                elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);


// Compute the average of your subset
    float sub_avg = compute_avg(sub_rand_nums, elements_per_proc);
// Gather all partial averages down to the root process
    float sub_avgs[world_size];
//float *sub_avgs = (float *)malloc(sizeof(float) * world_size);
    MPI_Allgather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT,
                  MPI_COMM_WORLD);

// Compute the total average of all numbers.
    float avg = compute_avg(sub_avgs, world_size);
    printf("Avg of all elements is %f from process %d\n", avg, world_rank);
    // Compute the average across the original data for comparison
    if (world_rank == 0) {
        float original_data_avg =
                compute_avg(rand_nums, elements_per_proc * world_size);
        printf("Avg computed across original data is %f\n", original_data_avg);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}