#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "qsort.h"

#include <errno.h>
#include <pthread.h>

#include "omp.h"


typedef struct thread_arg{
    int* arr;
    int len;
    int right_border;
    int left_border;
} thread_arg;

void printPartArr(int* arr, int left, int right){
    printf("[ ");
    int i;
    for(i = left; i < right; i++){
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void printArr(int* arr, int size){
    printf("[ ");
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void* _qsort__prll(void* arg){
    thread_arg tinfo = *(thread_arg*)arg;
    qsort__(tinfo.arr, tinfo.left_border, tinfo.right_border);
    return NULL;
}

void parallel_sort_of_parts(int* arr, int len){
    pthread_t thread[4];
    thread_arg* tinfo = calloc(4, sizeof(thread_arg));
    int left_b = 0, right_b = 0;
    int i = 0;
    for(; i < 4; i++){
        if(i != 3){
            left_b = i*(len/4);
            right_b = (i+1)*(len/4);
        }else{
            left_b = i*(len/4);
            right_b = len;
        }
        tinfo[i].arr = arr;
        tinfo[i].left_border  = left_b;
        tinfo[i].right_border = right_b-1;
        pthread_create(&thread[i], NULL, _qsort__prll, &(tinfo[i]));
    }
    int k = 0;
    for(; k < 4; k++){
        pthread_join(thread[0], NULL);
    }
    free(tinfo);
}

int* merge_sort(int* arr, int len, int left, int right){
    int k = 0;
    int i = left;
    int j = right;
    int* res = malloc((len-left)*sizeof(int));
    while(k < len-left){
        if( arr[i] < arr[j] && i < right){
            res[k++] = arr[i++];
        }else{
            if(j < len)
                res[k++] = arr[j];
            j++; //Warning inf loop
        }
        // printArr(res, len-left);
    }
    return res;
}

void* __merge_sort_prll(void* arg){
    thread_arg tinfo = *(thread_arg*)arg;
    int* tmp = merge_sort(tinfo.arr, tinfo.len, tinfo.left_border, tinfo.right_border);
    memcpy(tinfo.arr + tinfo.left_border, tmp, (tinfo.len - tinfo.left_border)*sizeof(int));
    free(tmp);
    return NULL;
}

void OddEvenSort(int* arr, int len){
    int i;
    for(i = 0; i < 4; i++){
        if(i%2 == 0){
            pthread_t thread1, thread2;
            thread_arg* tinfo = calloc(2, sizeof(thread_arg));
            tinfo[0].arr = arr;
            tinfo[0].len = (len/4)*2;
            tinfo[0].left_border = 0;
            tinfo[0].right_border = len/4;

            tinfo[1].arr = arr;
            tinfo[1].len = len;
            tinfo[1].left_border = (len/4)*2;
            tinfo[1].right_border = (len/4)*3;

            pthread_create(&thread1, NULL, __merge_sort_prll, &tinfo[0]);
            pthread_create(&thread2, NULL, __merge_sort_prll, &tinfo[1]);
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);
            free(tinfo);
        }else{
            pthread_t thread1;
            thread_arg* tinfo = calloc(1, sizeof(thread_arg));
            tinfo->arr = arr;
            tinfo->len = 3*(len/4);
            tinfo->left_border = len/4;
            tinfo->right_border = (len/4)*2;
            pthread_create(&thread1, NULL, __merge_sort_prll, &tinfo[0]);
            pthread_join(thread1, NULL);
            free(tinfo);
        }
    }
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int size_arr = 100000000;
    double start = 0, end = 0, diff_time = 0; 
    int* a = malloc(size_arr*sizeof(int));
    int i = 0;
    for(; i < size_arr; i++){
        a[i] = rand()%100; // min + rand()%(max - min)  
    }

    int l = 0;
    for(l = 100; l < size_arr; size_arr/=6 ){
        printf("size arrr : %d\n", size_arr);
        start = omp_get_wtime();
        qsort__(a, 0, size_arr);
        end = omp_get_wtime();
        printf("my_qsort time = %.16g\n", end - start);

        start = omp_get_wtime();
        qsort(a, size_arr, sizeof(int), cmpfunc);
        end = omp_get_wtime();
        printf("std_qsort time = %.16g\n", end - start);

        start = omp_get_wtime();
        parallel_sort_of_parts(a, size_arr);
        OddEvenSort(a, size_arr);
        end = omp_get_wtime();
        printf("prll_qsort time = %.16g\n", end - start);
    }
    // printArr(a, size_arr);
    
    return 0;
}

// 5 9 8 / 1 6 4 / 0 3 1 / 9 3 7

// 5 8 9 / 1 4 6 / 0 1 3 / 3 7 9



// 1 4 5  6 8 9 / 0 1 3  3 7 9

// 1 4 5 / 0 1 3 6 8 9 / 3 7 9

// 0 1 1 3 4 5  /  3 6 7 8 9 9

// 0 1 1 / 3 3 4 5 6 7 / 8 9 9
