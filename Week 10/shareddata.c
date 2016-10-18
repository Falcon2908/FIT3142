#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) { 
    int rank, value = 0;
    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while (value > = 0) {
        if(rank == 0)
            scanf("%d", &value);

        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        printf("Process %d recieved %d value\n",rank,value); 
    } 

    MPI_Finalize();
    return 0;
}