#include <stdio.h>
#include "mpi.h"
#include <string.h>

int main(int argc,char *argv[]){
	int size, rank, dest, source, count, tag=1;
	char msg='x';
    int sizeMsg=strlen(msg);
	MPI_Status Stat;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
	  dest = 1;
	  source = 1;
      strcpy(&msg,"Hello");
	  MPI_Send(msg, strlen(msg)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

	}
    
    else if (rank == 1) {
	  dest = 0;
	  source = 0;
      printf("Antes de recibir %s\n", msg); 
	  MPI_Recv(msg, strlen(msg)+1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat);
      printf("Despues de recibir %s\n", msg);
	 }

	MPI_Get_count(&Stat, MPI_CHAR, &count);
	printf("Task %d: Received %d char(s) from task %d with tag %d \n",
		   rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);

	MPI_Finalize();
}
