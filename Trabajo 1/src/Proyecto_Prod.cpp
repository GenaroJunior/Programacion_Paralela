/*
 ============================================================================
 Name        : Proyecto_Prod_Product.c
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
        if(size != 4)
        {
            printf("Contara con 4 procesos.\n");

        }

        int root_rank = 0;

        int my_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        int my_value = my_rank + 1;
        int reduction_result = 0;
        MPI_Reduce(&my_value, &reduction_result, 1, MPI_INT, MPI_PROD, root_rank, MPI_COMM_WORLD);

        if(my_rank == root_rank)
        {
            printf("El producto de todos los valores es %d.\n", reduction_result);
        }

        MPI_Finalize();

        return EXIT_SUCCESS;
    }
