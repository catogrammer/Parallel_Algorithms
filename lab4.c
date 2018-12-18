#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include "qsort.h"
#include "parallelqsort.h"

#include <errno.h>
#include <pthread.h>

void printArr(int* arr, int size){
    printf("[ ");
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf(" ]\n");
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
    int size_arr = 24;
    int* a = malloc(size_arr*sizeof(int));
    int i = 0;
    for(; i < size_arr; i++){
        a[i] = rand()%9; // min + rand()%(max - min)  
    }
    qsort__(a, 0, size_arr);
    printArr(a, size_arr);


    
    return 0;
}

// 5 9 8 / 1 6 4 / 0 3 1 / 9 3 7

// 5 8 9 / 1 4 6 / 0 1 3 / 3 7 9



// 1 4 5  6 8 9 / 0 1 3  3 7 9

// 1 4 5 / 0 1 3 6 8 9 / 3 7 9

// 0 1 1 3 4 5  /  3 6 7 8 9 9

// 0 1 1 / 3 3 4 5 6 7 / 8 9 9
