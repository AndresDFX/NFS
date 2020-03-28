#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "mpi.h"

int main(){
 
  char hostname[HOST_NAME_MAX + 1];
  gethostname(hostname, HOST_NAME_MAX + 1);
  MPI_Init(NULL, NULL);  
 
  printf("Wonderful Class from host %s!\n",hostname);
 
  MPI_Finalize();

  return(0);
}