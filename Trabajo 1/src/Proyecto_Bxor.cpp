/*
 ============================================================================
 Name        : Proyecto_Bxor_BitwiseExclusiveOr.c
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
    if(size != 8)
    {
        printf("Contara con 8 procesos.\n");
    }

    int root_rank = 0;

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    char all_values[8] = {0, 1, 7, 2, 6, 3, 5, 8};
    char my_value = all_values[my_rank];
    char reduction_result = 0;
    MPI_Reduce(&my_value, &reduction_result, 1, MPI_UNSIGNED_CHAR, MPI_BXOR, root_rank, MPI_COMM_WORLD);

    if(my_rank == root_rank)
    {
        printf("La exclusiva Bitwise final es %d.\n", reduction_result);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
