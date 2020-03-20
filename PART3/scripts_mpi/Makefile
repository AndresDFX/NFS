run: compile
	mpirun -np 4 --hostfile machinefile ./mpiExample
compile:
	mpicc mpiExample.c -o mpiExample
clean:
	rm -rf mpiex
