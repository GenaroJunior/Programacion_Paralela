/*
 ============================================================================
 Name        : Proyecto_SumarDosVectores.c
 Author      : Junior
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */



#include <math.h> 
#include "mpi.h" 
#include <iostream>

using namespace std;
 
int main(int argc, char *argv[]) {
	int m, rank, size;
	MPI::Init(argc, argv);

	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();


	if (rank == 0) {
		m=100;
		int x[m], y[m], z[m];
		for(int i=0;i<100;i++){
			x[i]=y[i]=i;
		}
		for(int i=1;i<10;i++){
			MPI_Send(x+i*10, m/size, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(y+i*10, m/size, MPI_INT, i, 1, MPI_COMM_WORLD);
		}
		for(int i=0;i<m/size;i++){
			z[i]=x[i]+y[i];
		}
		for(int i=1;i<10;i++){
			MPI_Recv(z+i*10, 10, MPI_INT, i, i+1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
		for(int i=0;i<100;i++){
			cout<<z[i]<<endl;
		}
	 }

	else{
		int local_x[10], local_y[10], local_z[10];
		MPI_Recv(local_x, 10, MPI_INT, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(local_y, 10, MPI_INT, 0, 1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

		for(int i=0;i<10;i++){
			local_z[i]=local_x[i]+local_y[i];
		}
		MPI_Send(local_z, 10, MPI_INT, 0, rank+1, MPI_COMM_WORLD);
	}

	MPI::Finalize();
	return 0;
}
