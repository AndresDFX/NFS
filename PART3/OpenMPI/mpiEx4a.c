#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int i, sum=0, sumTotal=0, upToVal, insum=0;
	int start, end, size, rank;
	MPI_Status Stat;

	upToVal = 10000;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Definning the part of the sum each process will perform */
	int offset = upToVal / size;
	start = rank * offset + 1;
	end = offset * (rank + 1);

	/* Each process performs its part of the sum */
	sum = 0;
	for(i=start; i<= end; i++){
		sum = sum +i;
	}

	/* If I am rank 0 process */
	if( rank == 0 ){
		/* I will recive the partials sums of rank > 0 process */
		for(i=1;i<size;i++){
			MPI_Recv(&insum, 1, MPI_INT, i, 1, MPI_COMM_WORLD,&Stat);
			sumTotal += insum;
		}
		/* Then I put my part of the sum to the total */
		sumTotal = sum;
		/* Finally I will print the total sum */
		printf ("\nTotal: %d\n",sumTotal);

	}else{
		/* 
			On the other hand, If I am NOT rank 0 process, 
			I will send my part of the sum to rank 0 process
		*/
		MPI_Send(&sum,1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	
	return 0;
}