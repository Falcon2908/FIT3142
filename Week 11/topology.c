#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, value = 0, reorder = 0;
    int right_n, left_n;

    MPI_Comm ring;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Cart_create(MPI_COMM_WORLD, 1, &size, &reorder, 1, &ring);
    MPI_Cart_shift(ring, 0, 1, &left_n, &right_n);
    MPI_Comm_rank(ring, &rank);
    MPI_Comm_size(ring, &size);

    while(value >= 0) {
        if(rank == 0) {
            scanf("%d", &value);
            MPI_Send(&value, 1, MPI_INT, right_n, 0 , ring);
        }
        else {
            MPI_Recv(&value, 1, MPI_INT, left_n, 0 , ring, &status );

            if(rank < size - 1)
                MPI_Send(&value, 1, MPI_INT, right_n, 0 , ring);
        }

        printf("Process %d of %d recieved %d\n", rank, size, value);
    } 
    MPI_Finalize();
    return 0;
}