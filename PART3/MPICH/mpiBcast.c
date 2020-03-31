 #include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
 
#define MAXVECT 10
#define MAXPROC 5
#define imprimirvector printf("Mi vista (%d) del vector\n",myrank); for (i = 0 ; i < MAXVECT; i++) printf("[%d: %d] ",myrank,vector[i]); printf("\n");

int main(int argc, char *argv[])
{
    int myrank, worldsize;
    int i;
    int vector[MAXVECT];
    char hostname[HOST_NAME_MAX + 1];

    gethostname(hostname, HOST_NAME_MAX + 1);
    srand(time(NULL));
    // Escriba las lineas que permitan:
    //  (1) Inicializar el dominio MPI
    //  (2) Guardar en la variable 'worldsize' el numero de procesos 
    // involucrados en la ejecucion de esta app
    //  (3) Guardar el rango del proceso
    //
    // (1)
    MPI_Init(NULL, NULL);
    // (2)
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    // (3)
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int choosen = (rand()%worldsize); 

    if (myrank == choosen) {
      imprimirvector
    }
    if (myrank == 1) { // proceso con rango 0 inicializara el vector
      for (i = 0; i < MAXVECT; i++)
        vector[i] = i;
    }
    // Escriba la linea que permite distribuir el vector con la instruccion
    // MPI_Bcast
    //
    // (4)
    MPI_Bcast(&vector, MAXVECT, MPI_INT,  0, MPI_COMM_WORLD);
    if (myrank == choosen) {
      imprimirvector
    }
    // Inserta la instruccion que termina el contexto de ejecucion de MPI
    //
    // (5)
    MPI_Finalize();
    return 0;
}

