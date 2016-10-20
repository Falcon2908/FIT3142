#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    double start, finish, partial, sum, calc, pi, localpi;
    int rank, n, size, complete=0, i;

    MPI_Init(&argc, &argv);
    start = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    n = atoi(argv[1]);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    partial = 1.0 / (double) n;
    sum = 0.0;
    for (i = rank + 1; i<= n; i+=size) {
            calc = partial * ((double) i - 0.5);
            sum += 4.0 / (1.0 + calc * calc);
    }
    
    localpi = partial * sum;

    MPI_Reduce(&localpi , &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        printf("Pi %lf\n", pi);
    }
    finish = MPI_Wtime();
    MPI_Finalize();
    printf("Parallel Elapsed time: %f seconds\n", finish-start);
}