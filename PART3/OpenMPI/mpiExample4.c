#include <stdio.h>
#include "mpi.h"

int main(int argc,char *argv[]){
	int i, maxVal;
	int start, end, size, rank;
	unsigned long sum, sumTotal;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Defina aqui el segmento que debe procesar una tarea
	// El inicio del segmento en la variable 'start', el fin del segmento
	// la variable 'end'
	sum = 0;
	
	 if(rank==0)
	 {
		start=1;
	        end=20000;
            	for(i=start; i<= end; i++)
		{
		 sum = sum +i;
            	}
	 }
	else	  
	if(rank==1)
	{
		start=20001;
	        end=40000;
            	for(i=start; i<= end; i++)
		{
		  sum = sum +i;
            	}
	 }
	 else 
	if(rank==2)
	{
		start=40001;
		end=60000;
		for(i=start; i<= end; i++)
		{
		sum = sum +i;
            	}
	 }
	else	 
	if(rank==3)
	{
		start=60001;
		end=80000;
            	for(i=start; i<= end; i++)
		{
		 sum = sum +i;
				
            	}
	 }
	else	 
	 if(rank==4)
	{
		start=80001;
	        end=100000;
            	for(i=start; i<= end; i++)
		{
			sum= sum+i;
           	}
	 }
	
         printf("Proceso :  %d - Suma Parcial:  %lu  - desde: %d- hasta %d\n",rank ,  sum , start, end );
        

	MPI_Reduce(&sum, &sumTotal, 1 , MPI_UNSIGNED_LONG, MPI_SUM , 0 , MPI_COMM_WORLD);
	// Utilice la funcion 'MPI_Reduce' para guardar en la variable 
	// 'sumTotal' la suma parcial de todos las tareas 

	if(rank==0)
	{
		printf ("\nSuma Total: %lu\n",sumTotal);
	}

	MPI_Finalize();
	
	return 0;
}
