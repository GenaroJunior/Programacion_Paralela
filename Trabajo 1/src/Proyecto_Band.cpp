/*
 ============================================================================
 Name        : Proyecto_Band_BitwiseAnd.c
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
        if(size != 6)
        {
            printf("Contara con 6 procesos.\n");

        }

        int root_rank = 0;

        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        char all_values[6] = {0, 2, 1, 3, 7, 5};
        char my_value = all_values[my_rank];
        char reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BAND, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El bitwise final es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
