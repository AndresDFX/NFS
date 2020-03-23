#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	srand(time(NULL));
	int i, count, countTotal, npoints;
	int start, end, rank, size, offset;
	double x, y;

	/* Total number of points to generate */
	npoints = 100000000;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	/* Each process sum to its count variable */
	count = 0;
	int my_number_of_points = npoints / size;
	for (i = 0; i < my_number_of_points; ++i)
	{
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		/* if the point fall inside the circle */
		if(x * x + y * y <= 1.0) count ++;
	}

	MPI_Reduce(&count,&countTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0) printf ("\nTotal: %f\n", ( (double)countTotal / npoints) * 4.0);

	MPI_Finalize();
	
	