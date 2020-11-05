#include <mpi.h>
#include <stdio.h>
double f(double x)
{
return 4./(1 + x * x);
}
main(int argc, char* argv[])
{
int r;
int p;
int i;
double sum;
double h;
MPI_Status st;
double t;
int n = 100000000;
double a = 0.0;
double b = 1.0;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &r);
MPI_Comm_size(MPI_COMM_WORLD, &p);
if(r == 0)
t = MPI_Wtime();
sum = 0.0;
h = (b - a) / n;
for(i = r; i < n; i += p)
sum += f(a + (i + 0.5) * h);
sum *= h;

if(r != 0) {
MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
} else {
double s;
for(i = 1; i < p; i ++) {
MPI_Recv(&s, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
sum += s;
}
t = MPI_Wtime() - t;
printf("Integral value = %lf. Time = %lf sec.\n", sum, t);
}
MPI_Finalize();

}