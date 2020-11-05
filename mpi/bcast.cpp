# include <mpi.h>

# include <stdio.h>

# include <string.h>

int main(int argc, char* argv[])

{

int numtasks, rank, root;

root = 0;

MPI_Init(&argc,&argv);

MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

int arraySize = 10; 
int array[arraySize];
     for (int i = 0; i < arraySize; ++i) {
         array[i] = rank;
     }

MPI_Bcast(array, 16, MPI_INT, root, MPI_COMM_WORLD);


printf("Hi, i'm number %d and i got:", rank);
for (int elemIdx = 0; elemIdx < arraySize; ++elemIdx) {
                 printf("%d ", array[elemIdx]);
             }
             printf("\n");
MPI_Finalize();

}