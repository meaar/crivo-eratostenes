#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER 50

int main(){
    int i,j;
    int max = sqrt(NUMBER);
    int *vet = malloc(NUMBER*sizeof(int));
    for (i=0; i < NUMBER-1; i++){
        vet[i] = i+2;
    }
    for (i=2; i <= max; i++){
        for (j=i+1; j <= NUMBER; j++){
            if (j%i == 0){
                vet[j-2] = -1;
            }
        }
    }
    for (i=0; i < NUMBER-1; i++){
        printf("[%d]\n",vet[i]);
    }
    return 0;
}