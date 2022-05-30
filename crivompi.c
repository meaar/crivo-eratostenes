#include <mpi.h>
#include <stdio.h>


int main(int argc, char** argv) {
    //Iniciando MPI
    MPI_Init(NULL, NULL);
    int ncpus;
    MPI_Comm_size(MPI_COMM_WORLD, &ncpus);
    int meu_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_rank);
    
    printf("Hello World!\n");

    MPI_Finalize();
}