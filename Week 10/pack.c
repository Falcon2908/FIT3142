#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, packsize, position, i;
    double d;
    char packbuff[100];

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    do {
        if ( rank ==0 ) {
            scanf("%d", &i);
            scanf("%lf", &d);
            packsize = 0;
            MPI_Pack(&i, 1, MPI_INT, packbuff, 100, &packsize, MPI_COMM_WORLD);
            MPI_Pack(&d, 1, MPI_DOUBLE, packbuff, 100, &packsize, MPI_COMM_WORLD);
        }
        
        MPI_Bcast( &packsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(packbuff, packsize, MPI_PACKED, 0, MPI_COMM_WORLD);
        
        if(rank != 0) {
            position = 0;
            MPI_Unpack(packbuff, packsize, &position, &i, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(packbuff, packsize, &position, &d, 1, MPI_DOUBLE, MPI_COMM_WORLD);            
        }

        printf("Process %d recieved %d and %lf\n", rank, i, d);
    } while (i >= 0);

    MPI_Finalize();
    return 0;
}