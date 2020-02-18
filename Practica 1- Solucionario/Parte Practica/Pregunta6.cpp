/*
 ============================================================================
 Name        : Solucion_Pregunta_P06.c
 Author      : Junior
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
    int n, x, ref, lleg, sz, rank;
    vector<int> VectorA, VectorA_Lleg;

    srand(time(NULL));

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout<<"Resol del Problema06"<<endl;
    cout<<"Numero de veces que se repite un numero"<<endl;

    if (rank == 0) {
        cout << "Digite el tamaño del Vector: ";
        cin>>n;
        VectorA.resize(n, 0);
        cout<< "\nVector A generado :"<<endl;
		for(int i=0;i<n;i++){
        	VectorA[i]=rand()%10;
        	cout<<VectorA[i]<<" ";
		}
		cout << "\nDiga el valor a buscar : ";
		cin>>x;
    }
    VectorA_Lleg.resize(n/sz, 0);
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Scatter(&VectorA[0], n/sz, MPI_INT, &VectorA_Lleg[0], n/sz, MPI_INT, 0, MPI_COMM_WORLD);

    ref = 0;

    for (int i = 0; i < n/sz; ++i) {
    	if (VectorA_Lleg[i]==x)
        	ref ++;
    }

    MPI_Reduce(&ref, &lleg, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
        cout << "La cantidad que se repite el valor es = " << lleg << endl;

    MPI_Finalize();
    return 0;
}

