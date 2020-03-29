/**Usando la función MPI_Scatter() y MPI_Gather() calcule de manera distribuida el promedio de un vector de tamaño N. A continuación el algoritmo:
Genere un arreglo de tamaño N con N números aleatorios.
Distribuya el contenido del vector entre todos los procesos que forman parte de la ejecución de la aplicación de modo que a cada proceso le toque la misma cantidad de elementos del vector.
Cada proceso calcula su promedio.
Se reúne el promedio de cada proceso y se calcula el promedio de esos promedios parciales.

Modifique el programa anterior de modo que se use la función MPI_Reduce(). La función MPI_Reduce() lo que deberá hacer es sumar los promedios parciales de cada proceso y el proceso que reciba los datos deberá dividir el valor recibido por el número de procesos que llevaron a cabo la ejecución de la aplicación.
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>

//Imprimir vector de un tamaño n
void printarray(int n, float *array) {
	int i = 0;
	printf("[ ");
	for (; i < n; i++) {
		if (i == n - 1) 
			printf("%f ", array[i]);
		else
			printf("%f, ", array[i]);
	}
	printf("]\n");
}

//Crear vector de numeros aleatorios del 1 al 100
float *create_rand_nums(int num_elements) {
  float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
  assert(rand_nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    rand_nums[i] = rand()%100+1;
  }
  return rand_nums;
}

// Calcula el promedio de un arreglo de flotantes
float compute_avg(float *array, int num_elements) {
  float sum = 0.f;
  int i;
  for (i = 0; i < num_elements; i++) {
    sum += array[i];
  }
  return sum / num_elements;
}

int main(int argc, char** argv) {

  if (argc != 2) {
    fprintf(stderr, "\nEspecificiar numero de elementos del arreglo asi: \nmpirun -n 4 -f host4file ./mpidemo 100 \nPara un arreglo de tamaño 100 que genera numeros aleatorios del 1 al 100\n\n");
    exit(argc);
    
  }

  //Convierte el numero pasado por argumento en el numero de elementos del arreglo
  int num_elements_per_proc = atoi(argv[1]);

  // Inicializa para que en cada ejecucion sean numeros random diferentes
  srand(time(NULL));
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);


  // Crea un arreglo de elementos en el proceso raíz. Su total
  // tamaño será el número de elementos por proceso multiplicado por el número
  // de procesos
  float *rand_nums = NULL;

  if (world_rank == 0) {
    rand_nums = create_rand_nums(num_elements_per_proc * world_size);
  }


  // Para cada proceso, cree un búfer que contendrá un subconjunto de toda la matriz
  float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);
  assert(sub_rand_nums != NULL);

  // Dispersa los números aleatorios del proceso raíz a todos los procesos en el mundo MPI
  MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums,
              num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // Calcula el promedio de cada subarreglo
  float sub_avg = compute_avg(sub_rand_nums, num_elements_per_proc);

  
  // Reduce todos los promedio locales en una suma global
  float global_sum;
  MPI_Reduce(&sub_avg, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Ahora que tenemos la suma global dividimos por el tamaño de los procesos para calcular el promedio
  if (world_rank == 0) {
    float avg =  global_sum /world_size ;
    printf("El promedio de todos los elementos: %f\n", avg);

     // Calcular el promedio de los datos originales para comparar, los dos deben ser iguales
    float original_data_avg = compute_avg(rand_nums, num_elements_per_proc * world_size);
    printf("El promedio calculado a través de los datos originales es %f\n", original_data_avg);
    printf("El arreglo original:\n");
    printarray(num_elements_per_proc * world_size,rand_nums);

  }

  //Limpiar los punteros
  if (world_rank == 0) {
    free(rand_nums);
  }
  free(sub_rand_nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
