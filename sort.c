#include <stdio.h>
#include <stdlib.h>

void printArr(int* arr, int size){
    printf("[ ");
    int i;
    for(i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf(" ]\n");
}

int* sorting(int* arr1, int* arr2, int size1, int size2){
    int* res = malloc((size1 + size2)*sizeof(int));
    int k = 0;
    int i = 0;
    int j = 0;
    while( k < size1 + size2){
        // printf("i = %d j = %d k = %d\n", i, j, k);
        if( arr1[i] < arr2[j]){
            res[k++] = arr1[i++];
        }else{
            if( j < size2)
                res[k++] = arr2[j];
            j++; //Warning inf loop
        }
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int arr1[6] = {-4, 0, 3, 6, 8, 9};
    int arr2[8] = {-2, -1, 0, 2, 3, 6, 7, 9};
    printArr(sorting(arr2, arr1, 8, 6), 6+8);
    
    return 0;
}
