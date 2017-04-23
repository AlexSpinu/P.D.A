#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define INF 999
#define SIZE 4

int main(int argc, char *argv[])

{
	int i;
	int j;
	int k;
	int mat[SIZE][SIZE] = {

		{0,   8,  INF,    1 },
		{INF,   0,  1,	INF },
		{4,  INF,  0,   INF },
		{INF, 2,  9,    0 },

	};

	int min[SIZE][SIZE];


	int numprocs, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	for (k = 0; k < SIZE; k++)
	{
		for (i = rank; i < SIZE; i = i + numprocs)
		{
			for (j = 0; j < SIZE; j++)
			{
				if (mat[i][k] + mat[k][j] < mat[i][j])

					mat[i][j] = mat[i][k] + mat[k][j];
			}
		}

		MPI_Allreduce(mat, min, SIZE * SIZE, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

		if (rank == 0)
		{
			printf("The min costs are ");

			for (i = 0; i < SIZE; i++)
			{
				for (j = 0; j < SIZE; j++)
				{
					printf("%d ", min[i][j]);
				}
				printf("\n");
			}

	}

	MPI_Finalize();

	
	}

}

