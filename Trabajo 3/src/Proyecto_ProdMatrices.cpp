/*
 ============================================================================
 Name        : Proyecto_ProdMatricesMod.c
 Author      : Junior
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "mpi.h"

using namespace std;

int main(int argc, char * argv[]) {

    int numeroProcesadores,
            idProceso,fila,columna;
    long **A, 
            *x, 
            *y, 
            *miFila, 
            *comprueba;

    double tInicio,
            tFin; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numeroProcesadores);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProceso);

    if(idProceso == 0){
    	do{ cout<<"PRODUCTO DE MATRICES"<<endl;
    		cout<<"El numero de Filas debe ser igual al N de procesos"<<endl;
    		cout<<"Cantidad de filas (1-"<<numeroProcesadores<<"): ";
    		cin>>fila;
    		if(fila>numeroProcesadores) cout<<"Numero fuera de rango\n";
    	}while(fila>numeroProcesadores);
    	cout<<"Cantidad de columnas: ";
    	cin>>columna;
    	MPI_Bcast(&fila,1,MPI_INT,0,MPI_COMM_WORLD);
    	MPI_Bcast(&columna,1,MPI_INT,0,MPI_COMM_WORLD);
    }
    else{
    	MPI_Bcast(&fila,1,MPI_INT,0,MPI_COMM_WORLD);
    	MPI_Bcast(&columna,1,MPI_INT,0,MPI_COMM_WORLD);
    }


    A = new long *[fila];
    x = new long [columna]; 
   

   
    if (idProceso == 0) {
        A[0] = new long [fila * columna];
        for (unsigned int i = 1; i < fila; i++) {
            A[i] = A[i - 1] + columna;
        }
   
        y = new long [fila];

   
        srand(time(0));
        cout << "La matriz y el vector generados son " << endl;
        for (unsigned int i = 0; i < fila; i++) {
            for (unsigned int j = 0; j < columna; j++) {
                if (j == 0) cout << "[";
                A[i][j] = rand() % 10;
                cout << A[i][j];
                if (j == columna - 1){
                	cout << "]";
                	if(i<columna){
                		x[i] = rand() % 10;
                		cout << "\t  [" << x[i] << "]";
                	}
                	cout<< endl;
                }
                else cout << "  ";
            }
        }
        for (unsigned int k = fila; k < columna; k++) {
        	if(k<columna){
        	   x[k] = rand() % 10;
        	   cout << "\t\t  [" << x[k] << "]";
        	   cout<<endl;
        	}
        }
        cout << "\n";

   
        comprueba = new long [fila];
   
        for (unsigned int i = 0; i < fila; i++) {
            comprueba[i] = 0;
            for (unsigned int j = 0; j < columna; j++) {
                comprueba[i] += A[i][j] * x[j];
            }
        }
    }

   
    miFila = new long [columna];

   .
    MPI_Scatter(A[0], 
            columna, 
            MPI_LONG, 
            miFila, 
            columna, 
            MPI_LONG, 
            0, 
            MPI_COMM_WORLD); 

    
    MPI_Bcast(x,
            columna,
            MPI_LONG, 
            0, 
            MPI_COMM_WORLD); 


    
    MPI_Barrier(MPI_COMM_WORLD);
    
    tInicio = MPI_Wtime();

    long subFinal = 0;
    for (unsigned int i = 0; i < columna; i++) {
        subFinal += miFila[i] * x[i];
    }

    
    MPI_Barrier(MPI_COMM_WORLD);
    
    tFin = MPI_Wtime();

    
    MPI_Gather(&subFinal, 
            1, 
            MPI_LONG, 
            y, 
            1, 
            MPI_LONG, 
            0, 
            MPI_COMM_WORLD); 

    
    MPI_Finalize();

    if (idProceso == 0) {

        unsigned int errores = 0;

        cout << "El resultado obtenido y el esperado son:" << endl;
        for (unsigned int i = 0; i < fila; i++) {
            cout << "\t" << y[i] << "\t|\t" << comprueba[i] << endl;
            if (comprueba[i] != y[i])
                errores++;
        }

        delete [] y;
        delete [] comprueba;
        delete [] A[0];

        if (errores) {
            cout << "Hubo " << errores << " errores." << endl;
        } else {

        	cout << "Compilacion Satisfacctoria" << endl;
            cout << "El tiempo de ejecucion:  " << tFin - tInicio << " segundos." << endl;
        }

    }

    delete [] x;
    delete [] A;
    delete [] miFila;

}
