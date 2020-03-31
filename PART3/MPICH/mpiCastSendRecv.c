#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include "mpi.h"

#define MAXARRAY 10

//Metodo que inicializa un arreglo de n posiciones
int iniarray(int n, int *array)
{
    int i;
    for (i = 0; i < n; i++)
        array[i] = i;
    return i;
}

//Metodo que imprime un arreglo de n posiciones
void printarray(int n, int *array)
{
    int i = 0;
    printf("[ ");
    for (; i < n; i++)
    {
        if (i == n - 1)
            printf("%d ", array[i]);
        else
            printf("%d, ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char **argv)
{

    int myid, numprocs, left, right, countProcess, tag = 1;
    int countEven, countOdd;
    int buffer[MAXARRAY];

    MPI_Request request;
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    //Se inicializa el arreglo completo
    iniarray(MAXARRAY, buffer);

    //Recorre los nodos en orden contrario a las manecillas del reloj
    right = (myid + 1) % numprocs;
    left = myid - 1;
    if (left < 0)
        left = numprocs - 1;

    //Determinar cuantos elementos debe tener el arreglo de enteros impares dado el intervalo [0,9]
    countOdd = buffer[9] - buffer[0];

    if (countOdd % 2 == 0)
    {
        countOdd /= 2;
    }
    else if (countOdd % 2 == 1)
    {
        countOdd += 1;
        countOdd /= 2;
    }

    //Determina cuantos elementos son pares en el arreglo
    countEven = MAXARRAY - countOdd;

    if (right % 2 == 0)
    {

        int bufferPar[countEven];
        int bufferRec[countEven];
        int j = 0;

        for (int i = 0; i < MAXARRAY; i++)
        {
            if (buffer[i] % 2 == 0)
            {
                bufferPar[j] = buffer[i];
                j++;
            }
        }

        MPI_Sendrecv(bufferPar, countEven, MPI_INT, left, tag, bufferRec, countEven, MPI_INT, right, tag, MPI_COMM_WORLD, &status);
        printf("\nEl arreglo recibido en proceso par:\n");
        printarray(countEven,bufferRec);
    }

    else
    {

        int bufferImpar[countOdd];
        int bufferRec[countEven];
        int j = 0;

        for (int i = 0; i < MAXARRAY; i++)
        {
            if (buffer[i] % 2 != 0)
            {
                bufferImpar[j] = buffer[i];
                j++;
            }
        }

        MPI_Sendrecv(bufferImpar, countOdd, MPI_INT, left, tag, bufferRec, countOdd, MPI_INT, right, tag, MPI_COMM_WORLD, &status);
        printf("\nEl arreglo recibido en proceso impar:\n");
        printarray(countOdd,bufferRec);
    }

    MPI_Get_count(&status, MPI_INT, &countProcess);
    printf("Tarea %d: Recibe  %d int(s) desde tarea %d con tag %d \n",
           myid, countProcess, status.MPI_SOURCE, status.MPI_TAG);

    MPI_Finalize();
}
