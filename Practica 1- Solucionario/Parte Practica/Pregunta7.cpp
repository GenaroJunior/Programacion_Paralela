/*
 ============================================================================
 Name        : Solucion_Pregunta_P07.c
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

    int cant, sz, rank;
    long long int ref, lleg;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout<< "Resol. del Problema 07"<<endl;
    cout<< "Factorial de n! "<<endl;

    if (rank == 0) {
        cout << "Digite la cantidad de elementos : ";
        cin>>cant;
    }

    MPI_Bcast(&cant,1,MPI_INT,0,MPI_COMM_WORLD);

    ref = 1;
    for (int i = 0; i < cant/ sz; i++) {
    	ref *= sz*i+rank+1;
    }

    MPI_Reduce(&ref, &lleg, 1, MPI_LONG_LONG_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    if (rank == 0)
        cout <<cant<< "! = " << lleg << endl;

    MPI_Finalize();
    return 0;
}




