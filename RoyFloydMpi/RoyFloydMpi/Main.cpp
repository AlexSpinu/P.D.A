#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#define MASTER 0
#define WORKTAG 1
#define DIETAG 2
#define n 5 //Number of nodes

int dist[n][n]; /* dist[i][j] is the length of the edge between i and j if
				it exists, or 0 if it does not */

void printDist() {
	int i, j;
	printf("    ");
	for (i = 0; i < n; ++i)
		printf("%4c", 'A' + i);
	printf("\n");
	for (i = 0; i < n; ++i) {
		printf("%4c", 'A' + i);
		for (j = 0; j < n; ++j)
			printf("%4d", dist[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[]) {

	int my_rank,                
		num_procs,              
		slice,
		ypoloipo = 0;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	
	if (my_rank == MASTER) {
		int disable = 0;
		int t = 3;
		int result[3];
		//initialize dist[][]
		int i, j;
		for (i = 0; i < n; ++i)
			for (j = 0; j < n; ++j)
				if (i == j)
					dist[i][j] = 0;
				else
					dist[i][j] = rand() % 10 + 1;

		printDist();
		
		for (i = 1; i<num_procs; i++)
			MPI_Send(&dist, n*n, MPI_INT, i, WORKTAG, MPI_COMM_WORLD);

		do {
			MPI_Recv(&result, t, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (status.MPI_TAG == DIETAG)
				disable++;
			else
				if (dist[result[1]][result[2]]>result[0])
					dist[result[1]][result[2]] = result[0];
		} while (disable < num_procs - 1);
		
		printDist();
		
	}
	
	MPI_Finalize();

	return 0;
}