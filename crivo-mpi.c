#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define NUMBER 100000000

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int nprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int i,j;
    int limit = (int)sqrt(NUMBER);
    int interval = (int)(NUMBER-2)/nprocs;
    int *vet = malloc(NUMBER*sizeof(int));
    int *subvet = malloc(interval*sizeof(int));
    int *result = malloc(NUMBER*sizeof(int));
    double start,end;
    if (rank == 0){
        for (i=0; i < NUMBER; i++){
            vet[i] = i+2;
        }
    }
    start = MPI_Wtime();
    MPI_Scatter(vet,interval,MPI_INT,subvet,interval,MPI_INT,0,MPI_COMM_WORLD);
    if (rank == 0){
        for (i=2; i <= limit; i++){
            for (j=i; j < interval; j++){
                if (subvet[j] % i == 0){
                    subvet[j] = -1;
                }
            }
        }
    }else{
        for (i=2; i <= limit; i++){
            for (j=0; j < interval; j++){
                if (subvet[j] % i == 0){
                    subvet[j] = -1;
                }
            }
        }
    }  
    MPI_Gather(subvet,interval,MPI_INT,result,interval,MPI_INT,0,MPI_COMM_WORLD);
    end = MPI_Wtime();
    if (rank == 0){
        for (i=0; i < NUMBER-2; i++){
            if (result[i] != -1){
               printf("[%d]\n", result[i]);
            }
        }
        printf("Tempo de Execução: %f\n", end-start);
    }
    MPI_Finalize();
    return 0;
}
