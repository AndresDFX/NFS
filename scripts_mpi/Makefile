run: compile
	mpirun -np 4 --hostfile machinefile ./mpiex
compile:
	mpicc mpiExample.c -o mpiex
clean:
	rm -rf mpiex
