#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <cstdlib> 
#include <ctime> 

using namespace std;

    
#define FIRST     0   
#define ELEMENT   10
#define MAXSIZE   100

int main(int argc, char *argv[])
{
	int   numprocs, rank;
	int position;
	int i;
	int x;
	int low, high;
	int maxPosition;
	int array[MAXSIZE];
	


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	srand(time(NULL));
	

	for (i = 0; i < MAXSIZE; i++) {
		array[i] = rand();
	}

	if (rank == FIRST) {
		for (i = 0; i < MAXSIZE; i++) {
			printf("%d ", array[i]);
		}

			for (i = 0; i < MAXSIZE; i++) {
				if (array[i] == ELEMENT) {
					position = i;
					printf("I got %d possition from process %d\n", position, rank);
					
				}
			}
	}
	//Broadcast data
	MPI_Bcast(array, MAXSIZE, MPI_INT, FIRST, MPI_COMM_WORLD);
	// add portion of data 
	x = MAXSIZE / numprocs; // must be an integer 
	low = rank * x;
	high = low + x;
	for (i = low; i < high; i++) {
		if (array[i] == ELEMENT) 
			position = i;	
	}
	MPI_Reduce(&position, &maxPosition, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (FIRST == rank) {
		printf("The max position is %d.\n", maxPosition);
		MPI_Finalize();
	}


}

