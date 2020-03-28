#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int myid, numprocs, left, right,countProcess;
    int buffer[10], buffer2[10];
    MPI_Request request;
    MPI_Status status;
 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
 
    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;
 
    MPI_Sendrecv(buffer, 10, MPI_INT, left, 123, buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &status);

    MPI_Get_count(&status, MPI_INT, &countProcess);
	printf("Tarea %d: Recibe  %d int(s) desde tarea %d con tag %d \n",
		   myid, countProcess, status.MPI_SOURCE, status.MPI_TAG);
    
    
    MPI_Finalize();
    return 0;
}