#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "qsort.h"
#include "parallelqsort.h"

#include <errno.h>
#include <pthread.h>

void printArr(int* const arr, int const len){
    int i = 0;
    printf("Arr: ");
    for( ; i < len; i++){
        printf("%i ", arr[i]);
    }
    printf("\n");
}

//for four thread 
void parallel_sort_even_odd(int* arr, int len){
    pthread_t thread[4];
    int low = 0, high = 0;
    int i = 0;
    for(; i < 4; i++){
        if(i != 3){
            low = i*(len/4);
            high = (i+1)*(len/4);

        }else{
            low = (i+1)*(len/4);
            high = len;
        }
        pthread_create(&thread[i], NULL, _qsort__prll, &id2);
    }

    int k = 0;
    for(; k < 4; k++){
        pthread_join(thread[k], NULL);
    }
    
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int size_arr = 34;
    int* a = malloc(size_arr*sizeof(int));
    int i = 0;
    for(; i < size_arr; i++){
        a[i] = rand()%9; // min + rand()%(max - min)  
    }
    qsort__(a, 0, size_arr);
    printArr(a, size_arr);

    
    return 0;
}
