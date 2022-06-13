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
    int *vet = malloc(NUMBER*sizeof(int));
    int *result = malloc(NUMBER*sizeof(int));
    double inicio,fim;

    if (rank == 0){
        for (i=0; i < NUMBER-1; i++){
            vet[i] = i+2;
        }
    }
    int intervalo = (int)((NUMBER-2)/nprocs);

    // if (intervalo*nprocs < NUMBER-2){
    //     intervalo++;
    // }
    
    MPI_Scatter(vet, intervalo, MPI_INT,vet, intervalo, MPI_INT, 0, MPI_COMM_WORLD);

    // for(i = 0; i < intervalo; i++){
    //   if(rank == 0){
    //         printf("%d-[%d]\n", i, vet[i]);
    //     }
    //     // if(rank == 1){
    //     //     printf("1-[%d]\n", vet[i]);
    //     // }  
    // }

    int aux = 1;
    if(rank != 0){
        aux = -1;
    }
    inicio = MPI_Wtime();
    for (i=2; i <= limit; i++){
        for (j=i+aux; j < NUMBER-1; j++){
            if (vet[j-2]%i == 0){
                vet[j-2] = -1;
            }
            
        }
    }
    
    // for(i = 0; i < intervalo; i++){
    //   //if(rank == 0){
    //     //    printf("%d-(%d)\n", i, vet[i]);
    //     //}
    //     if(rank == 1){
    //       printf("%d-(%d)\n", i, vet[i]);
    //     }  
    // }
    

    MPI_Allgather(vet,intervalo,MPI_INT,result,intervalo,MPI_INT,MPI_COMM_WORLD);
    fim = MPI_Wtime();
    if (rank == 0){
        for (i=0; i < NUMBER-2; i++){
            if ((result[i] != -1)){
               printf("%d-[%d]\n",i, result[i]);
            }
        }
        printf("Tempo de Execução: %f\n", fim - inicio);
    }
    
    
    MPI_Finalize();
    printf("Tempo de Execução: %f\n", fim - inicio);
}
