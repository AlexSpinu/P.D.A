#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stddef.h>




int main(int argc, char *argv[])
{

	int i, j, rank, nrprocs;
	int a[4][4] = { { 4,2,5,2 },{3,3,3,4 },{ 1,6,2,7 },{ 8,12,7,2 } };
	int b[4][4] = { { 10,12,4,7 },{ 11,2,8,4 },{ 3,6,1,1 } ,{ 2,7,15,1 } };
	int result[4][4];
	int aBff[4], resBff[4];
	int aux = 0;
	

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nrprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	 //scatter first matrix   
	MPI_Scatter(a, 4*4 / nrprocs, MPI_INT, aBff, 4*4 / nrprocs, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Bcast(b, 4*4, MPI_INT, 0, MPI_COMM_WORLD);
	

	
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				aux += aBff[j] * b[j][i];
			}
			resBff[i] = aux;
			aux = 0;
		}
	


	MPI_Gather(resBff, 4*4 / nrprocs , MPI_INT, result, 4*4 / nrprocs, MPI_INT, 0, MPI_COMM_WORLD);

	//print matrix
	if (rank == 0) {
		for (i = 0; i <4 ; ++i) {
			for (j = 0; j < 4; j++)
			{
				printf("%d  ", result[i][j]);
			}
			printf("\n");
		}
	}
		

	MPI_Finalize();
	exit(0);

}


