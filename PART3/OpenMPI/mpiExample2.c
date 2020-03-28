#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]){
	int  rank, size;
	
	/* start up MPI */
	
	MPI_Init(&argc, &argv);
	
	/* Guarda los identificadores unicos de cada proceso,generalmente entero consecutivos 0 es el master o proceso root*/
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	/* Almacena el numero de procesos */
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    	printf("Hello MPI World from process %d!\n", rank);

	if (rank == 1) 
		printf("[%d] Size: %d\n",rank, size);

	/* shut down MPI */
	MPI_Finalize(); 
	
	return 0;
}