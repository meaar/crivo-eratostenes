#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER 1000

int main(){
    int i,j;
    int limit = sqrt(NUMBER);
    int *vet = malloc(NUMBER*sizeof(int));
    for (i=0; i < NUMBER-1; i++){
        vet[i] = i+2;
    }
    for (i=2; i <= limit; i++){
        for (j=i+1; j <= NUMBER; j++){
            if (vet[j-2]%i == 0){
                vet[j-2] = -1;
            }
        }
    }
    for (i=0; i < NUMBER-1; i++){
        if (vet[i] != -1){
            printf("[%d]\n",vet[i]);
        }
    }
    return 0;
}
