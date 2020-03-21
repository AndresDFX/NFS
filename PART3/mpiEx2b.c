#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
  int rank, size;

  MPI_Init(NULL,NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) printf("Yo soy el maestro y existen %d procesos\n",size);
  MPI_Finalize();
}
