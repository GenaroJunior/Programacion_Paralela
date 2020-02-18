/*
 ============================================================================
 Name        : Proyecto_Max_Maximun.c
 Author      : Junior
 Version     :
 Copyright   : Your copyright notice
 Description : Calculate Pi in MPI
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


    int main(int argc, char* argv[])
    {
        MPI_Init(&argc, &argv);


        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        if(size != 5)
        {
            printf("Solo contara con 5 procesos. \n");

        }


        int root_rank = 0;


        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


        int reduction_result = 0;
        MPI_Reduce(&my_rank, &reduction_result, 1, MPI_INT, MPI_MAX, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El máximo es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
