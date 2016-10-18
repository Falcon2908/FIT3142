#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, blocklens[2];
    struct {int i; double d;} value;
    MPI_Datatype data, types[2];
    MPI_Aint disp[2];

    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    blocklens[0] = 1;
    blocklens[1] = 1;

    types[0] = MPI_INT;
    types[1] = MPI_DOUBLE;

    MPI_Address( &value.i, &disp[0]);
    MPI_Address( &value.d, &disp[1]);

    disp[1] = disp[1] - disp[0];
    disp[0] = 0;

    MPI_Type_struct (2, blocklens, disp, types, &data);
    MPI_Type_commit (&data);

    do {
        if (rank == 0)
        {
            scanf( "%d", &value.i);
            scanf( "%lf", &value.d);
        }

        MPI_Bcast (&value, 1, data, 0, MPI_COMM_WORLD);

        printf("Process %d recieved %d and %lf\n", rank, value.i, value.d);
    } while (value.i >= 0);

    MPI_Type_free( &data );
    MPI_Finalize;
    return 0;
}