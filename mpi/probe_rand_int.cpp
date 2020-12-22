#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(rank);

    const int arraySize = (rand() % 10) + 3;  // (rand() % 10)

    int *array = new int[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        array[i] = i;
    }

    const int RECEIVER = 0;
    const int TAG = 0;

    if (rank == RECEIVER) {
        for (int i = 0; i < size; ++i) {
            if (i == RECEIVER) {
                continue;
            }

            MPI_Status status;
            MPI_Probe(/*source*/ i, TAG, MPI_COMM_WORLD, &status);
            int count;
            MPI_Get_count(&status, MPI_INT, &count);

            printf("%d has %d elements:\n", i, count);

            int *receivedArray = new int[arraySize];

            MPI_Recv(receivedArray, /*count*/ count, MPI_INT, /*source*/ i, TAG, MPI_COMM_WORLD, &status);

            for (int elemIdx = 0; elemIdx < count; ++elemIdx) {
                printf("%d ", receivedArray[elemIdx]);
            }
            printf("\n");

            delete[] receivedArray;
        }
    } else {
        MPI_Send(array, /*count*/ arraySize, MPI_INT, /*receiver*/ RECEIVER, TAG, MPI_COMM_WORLD);
    }

    delete[] array;

    MPI_Finalize();
}