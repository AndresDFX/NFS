#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "mpi.h"

int main(int argc, char** argv) {
    int rank, size;
    int recvBuffer, sendBuffer;
    int tag = 0;

    char hostname[HOST_NAME_MAX + 1];
    gethostname(hostname, HOST_NAME_MAX + 1);
    MPI_Status status;

    /* Iniciando MPI*/
    MPI_Init(NULL,NULL);

	/* Guarda los identificadores unicos de cada proceso,generalmente entero consecutivos 0 es el master o proceso root*/
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	/* Almacena el numero de procesos */
	MPI_Comm_size(MPI_COMM_WORLD, &size);

    /*Se bloque porque ambos procesos se quedan recibiendo inicialmente*/
    if (rank == 0){
        MPI_Recv(&recvBuffer, 1, MPI_INT, dest+1, tag, MPI_COMM_WORLD, &status);
        MPI_Send(&sendBuffer, 1, MPI_INT, dest+1, tag, MPI_COMM_WORLD);
    } 
    else if(rank == 1){
        MPI_Recv(&recvBuffer, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &status);
        MPI_Send(&sendBuffer, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    }

    /*Imprimir interacciones */
    MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n",
		   rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);
    
    /*Cerrando el flujo de la aplicacion*/
    MPI_Finalize();
}
