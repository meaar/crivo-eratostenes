
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <math.h>

#define NUMBER 10000000

int main(){
    //Variaveis.
    int i,j,next;
    int limt;
    int cont;
    double inicio,fim;

    //Alocação do Vetor.
    int *vet = NULL;
    vet = malloc(NUMBER*sizeof(int));
    limt = (sqrt(NUMBER)) + 1;
    cont = 0;

    //Preenchimento do Vetor.
    for (i = 0; i < NUMBER-1; i++){
        vet[i] = i + 2;
    }

    //Execução do Crivo.
    inicio = omp_get_wtime();
    for (i = 2; i < limt; i++){
        #pragma omp parallel 
        {
            #pragma omp for
            for(j = i + 1; j <= NUMBER; j++){
                if(vet[j - 2] % i == 0){
                    vet[j - 2] = -1;
                }
            }
        }
    }
    fim = omp_get_wtime();
    
    //Resultado.
    printf("Numeros Primos: \n");

    for (i=0; i < NUMBER-1; i++){
        if(vet[i] != -1){
            printf("[%d]\n",vet[i]);
            cont++;
        }
    }
    printf("Quantidade de primos: %d\n", cont);

    printf("Tempo de Execução: %f\n", fim - inicio);

}

